#include "ModelObjState.h"

ModelObjState::~ModelObjState()
{
	resource_.Vertex.Reset();
	resource_.Material.Reset();
	resource_.Light.Reset();
	resource_.wvpResource.Reset();
}

void ModelObjState::Initialize(Model* state)
{
	SModelData ModelData_ = {};
	ModelData_ = ModelManager::GetObjData(state->GetModelHandle());
	state->SetTexHandle(ModelData_.material.handle);

	CreateResources::CreateBufferResource(sizeof(VertexData) * ModelData_.vertices.size(),resource_.Vertex);
    CreateResources::CreateBufferResource(sizeof(Material), resource_.Material);

	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * ModelData_.vertices.size(), resource_.Vertex.Get(), int(ModelData_.vertices.size()));
	if (state->GetUseLight())
	{
	    CreateResources::CreateBufferResource(sizeof(LightData), resource_.Light);
	}
	ModelData_.vertices.clear();
}

void ModelObjState::Draw(Model* state, const WorldTransform& worldTransform, const ViewProjection& viewprojection)
{
	VertexData* vertexData = nullptr;
	Material* materialData = nullptr;

	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
	resource_.Material->Map(0, nullptr, reinterpret_cast<void**>(&materialData));

	SModelData ModelData_ = {};
	ModelData_ = ModelManager::GetObjData(state->GetModelHandle());
	memcpy(vertexData, ModelData_.vertices.data(), sizeof(VertexData) * ModelData_.vertices.size());
	//ModelData_.vertices.clear();
	ImGui::Begin("direction");
	ImGui::SliderFloat3("t", &testLightDirection.x, -1.0f, 1.0f);
	ImGui::End();

	materialData->shininess = 70.0f;
	materialData->color = state->GetColor();
	materialData->uvTransform = MatrixTransform::AffineMatrix(state->GetuvScale(), state->GetuvRotate(), state->GetuvTranslate());
	if (state->GetUseLight())
	{
		LightData* lightData = nullptr;
		resource_.Light->Map(0, nullptr, reinterpret_cast<void**>(&lightData));

		lightData->color = { 1.0f,1.0f,1.0f,1.0f };
		lightData->direction = testLightDirection;
		lightData->intensity = 1.0f;

	}

	Commands commands = DirectXCommon::GetInstance()->GetCommands();
	SPSOProperty PSO = GraphicsPipelineManager::GetInstance()->GetPso().Sprite3d.none;
	if (state->GetUseLight())
	{
		PSO = GraphicsPipelineManager::GetInstance()->GetPso().Lighting;
	}

	commands.m_pList->SetGraphicsRootSignature(PSO.rootSignature.Get());
	commands.m_pList->SetPipelineState(PSO.GraphicsPipelineState.Get());

	commands.m_pList->IASetVertexBuffers(0, 1, &resource_.BufferView);

	commands.m_pList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	commands.m_pList->SetGraphicsRootConstantBufferView(0, resource_.Material->GetGPUVirtualAddress());
	commands.m_pList->SetGraphicsRootConstantBufferView(1, worldTransform.buffer_->GetGPUVirtualAddress());
	commands.m_pList->SetGraphicsRootConstantBufferView(2, viewprojection.buffer_->GetGPUVirtualAddress());
	DescriptorManager::rootParamerterCommand(3, state->GetTexHandle());
	if (state->GetUseLight())
	{
		commands.m_pList->SetGraphicsRootConstantBufferView(4, resource_.Light->GetGPUVirtualAddress());
		commands.m_pList->SetGraphicsRootConstantBufferView(5, viewprojection.buffer_->GetGPUVirtualAddress());
		DescriptorManager::rootParamerterCommand(6, LightingManager::dsvHandle());
		commands.m_pList->SetGraphicsRootConstantBufferView(7, LightingManager::GetBuffer()->GetGPUVirtualAddress());

	}

	commands.m_pList->DrawInstanced(UINT(ModelData_.vertices.size()), 1, 0, 0);

}
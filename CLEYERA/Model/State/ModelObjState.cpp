#include "ModelObjState.h"

ModelObjState::~ModelObjState()
{
	
}

void ModelObjState::Initialize(Model* state)
{

	//ModelData_ = ModelManager::GetObjData(state->GetModelHandle());
	state->SetTexHandle(state->GetModelData().material.handle);

	resource_.Vertex = CreateResources::CreateBufferResource(sizeof(VertexData) * state->GetModelData().vertices.size());

    if (state->GetUseLight())
	{
		resource_.Light = CreateResources::CreateBufferResource(sizeof(LightData));
	}


	resource_.BufferView = CreateResources::VertexCreateBufferView(sizeof(VertexData) * state->GetModelData().vertices.size(), resource_.Vertex.Get(), int(state->GetModelData().vertices.size()));

}

void ModelObjState::CallPipelinexVertex(Model* state)
{
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
}

void ModelObjState::Draw(Model* state, const WorldTransform& worldTransform, const ViewProjection& viewprojection)
{
	VertexData* vertexData = nullptr;
	
	resource_.Vertex->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));

	memcpy(vertexData, state->GetModelData().vertices.data(), sizeof(VertexData) * state->GetModelData().vertices.size());
	//ModelData_.vertices.clear();
	ImGui::Begin("direction");
	ImGui::SliderFloat3("t", &testLightDirection.x, -1.0f, 1.0f);
	ImGui::End();


	if (state->GetUseLight())
	{
		LightData* lightData = nullptr;
		resource_.Light->Map(0, nullptr, reinterpret_cast<void**>(&lightData));

		lightData->color = { 1.0f,1.0f,1.0f,1.0f };
		lightData->direction = testLightDirection;
		lightData->intensity = 1.0f;

	}

	Commands commands = DirectXCommon::GetInstance()->GetCommands();

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

	commands.m_pList->DrawInstanced(UINT(state->GetModelData().vertices.size()), 1, 0, 0);

}
#include "Game3dObject.h"

void Game3dObject::Create()
{
	MaterialBuffer_ = CreateResources::CreateBufferResource(sizeof(Material));

}

void Game3dObject::SetModel(uint32_t index)
{
	if (prevIndex_ != index)
	{
	    model_ = ModelManager::GetModel(index);
	}
	prevIndex_ = index;
}

void Game3dObject::Draw(WorldTransform worldTransform ,ViewProjection view)
{
	if (model_==nullptr)
	{
		return;
	}
	Material * materialData;
	MaterialBuffer_->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
	materialData->shininess = 70.0f;
	materialData->color = {1,1,1,1};
	materialData->uvTransform = MatrixTransform::Identity();
	model_->CommandCallPipelineVertex();

	Commands command = DirectXCommon::GetInstance()->GetCommands();

	command.m_pList->SetGraphicsRootConstantBufferView(0, MaterialBuffer_->GetGPUVirtualAddress());

	model_->Draw(worldTransform, view);
}

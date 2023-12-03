#include "Model.h"


Model::~Model()
{
	delete state_;
}

void Model::CreateModel(IModelState* state, Vector4 CenterPos , float size , Vector4 color)
{
	CenterPos_ = CenterPos;
	size_ = size;
	color_ = color;

	state_ = state;
	state_->Initialize(this);
}

void Model::CreateLine(IModelState* state,Vector4 StartPosition, Vector4 EndPosition, Vector4 Color)
{
	state_ = state;
	StartPos_ = StartPosition;
	EndPos_ = EndPosition;
	color_ = Color;
	state->Initialize(this);
}

void Model::SetModel(uint32_t handle)
{
	if (state_ != nullptr)
	{
		delete state_;
	}
	modelHandle_ = handle; 
	state_ = new ModelObjState();
	state_->Initialize(this);

}
void Model::Draw(WorldTransform worldTransform, ViewProjection viewprojection)
{
	if (state_ == nullptr)
	{
		LogManager::Log("None SetModel\n");
		assert(0);
	}
	worldTransform_ = worldTransform;
	state_->Draw(this, worldTransform_,viewprojection);
}

void Model::UseLight(SUseLight use)
{
	uselight_ = use;
}

Vector4 Model::ColorConversion(uint32_t rgbaValue)
{
	Vector4 result = {};
	result.x = ((rgbaValue >> 24) & 0xFF) / 255.0f; // Red
	result.y = ((rgbaValue >> 16) & 0xFF) / 255.0f; // Green
	result.z = ((rgbaValue >> 8) & 0xFF) / 255.0f;  // Blue
	result.w = (rgbaValue & 0xFF) / 255.0f;         // Alpha
	return result;
}


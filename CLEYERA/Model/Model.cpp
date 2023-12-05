#include "Model.h"

Model::~Model()
{
}

void Model::CreateModel(unique_ptr<IModelState> state, Vector4 CenterPos , float size , Vector4 color)
{
	CenterPos_ = CenterPos;
	size_ = size;
	color_ = color;

	state_.swap(state);
	state_->Initialize(this);
}

void Model::CreateLine(unique_ptr<IModelState> state,Vector4 StartPosition, Vector4 EndPosition, Vector4 Color)
{
	state_.swap(state);
	StartPos_ = StartPosition;
	EndPos_ = EndPosition;
	color_ = Color;
	state_->Initialize(this);
}

void Model::SetModel(uint32_t handle)
{
	prevModelHandle_ = modelHandle_;
	modelHandle_ = handle;

	if (prevModelHandle_ != modelHandle_)
	{
		state_.reset(new ModelObjState);
		state_->Initialize(this);
	}
}

void Model::Draw(WorldTransform worldTransform, ViewProjection viewprojection)
{
	if (state_ == nullptr)
	{
		LogManager::Log("None SetModel\n");
		assert(0);
	}
	
	state_->Draw(this, worldTransform,viewprojection);
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


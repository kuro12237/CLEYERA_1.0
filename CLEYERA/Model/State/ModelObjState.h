#pragma once
#include"IModelState.h"
#include"Model.h"
#include"ModelManager.h"

class ModelObjState :public IModelState
{
public:
	ModelObjState() {};
	~ModelObjState() {};

	void Initialize(Model* state)override;

	void Draw(Model* state, WorldTransform worldTransform, ViewProjection viewprojection)override;

private:

	SModelData ModelData_ = {};
	ResourcePeroperty resource_ = {};
};
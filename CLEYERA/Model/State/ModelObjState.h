#pragma once
#include"IModelState.h"
#include"Model.h"
#include"ModelManager.h"
#include"VectorTransform.h"

class ModelObjState :public IModelState
{
public:
	ModelObjState() {};
	~ModelObjState() ;

	void Initialize(Model* state)override;

	void Draw(Model* state, WorldTransform worldTransform, ViewProjection viewprojection)override;

private:
	ResourcePeroperty resource_ = {};
	Vector3 testLightDirection = { 0,-1.0f,0 };
};
#pragma once
#include"IModelState.h"
#include"Model.h"
#include"CreateResource.h"
#include"WorldTransform.h"
#include"GraphicsPipelineManager.h"

class ModelSphereState :public IModelState
{
public:
	
	~ModelSphereState() {};

	void Initialize(Model* state)override;

	void Draw(Model* state, WorldTransform worldTransform, ViewProjection viewprojection)override;


private:

	void CommandCall(Model*state, WorldTransform worldTransform, ViewProjection viewprojection);

	const int VertexNum = 16;
	ResourcePeroperty resource_ = {};
	Vector3 testLightDirection = { 0,-1.0f,0 };
	float shininess = 1.0f;
};


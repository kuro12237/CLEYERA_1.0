#pragma once

#include"IModelState.h"
#include"Model.h"
#include"CreateResource.h"
#include"WorldTransform.h"
#include"GraphicsPipelineManager.h"

class ModelCubeState :public IModelState
{
public:

	~ModelCubeState() {};

	void Initialize(Model* state)override;

	void Draw(Model* state, const WorldTransform& worldTransform, const ViewProjection& viewprojection)override;


private:

	void CommandCall(Model* state, const WorldTransform& worldTransform, const ViewProjection& viewprojection);

	const int VertexNum = 8;
	ResourcePeroperty resource_ = {};

};
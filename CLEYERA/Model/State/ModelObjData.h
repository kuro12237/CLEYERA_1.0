#pragma once
#include"pch.h"
#include"CreateResource.h"

class ModelObjData
{
public:
	
	ModelObjData(SModelData modelData, uint32_t index) { modelData_ = modelData, index_ = index; }
	~ModelObjData() {};

	SModelData GetData() { return modelData_; }
	uint32_t GetIndex() { return index_; }


private:

	SModelData modelData_;
	uint32_t index_;
};
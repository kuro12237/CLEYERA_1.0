#pragma once
#include"pch.h"
#include"CreateResource.h"

class ObjData
{
public:
	
	ObjData(SModelData modelData, uint32_t index) { modelData_ = modelData, index_ = index; }
	~ObjData() {};

	SModelData GetData() { return modelData_; }



private:

	SModelData modelData_;
	uint32_t index_;
};
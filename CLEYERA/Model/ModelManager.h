#pragma once
#include"Pch.h"
#include"ModelObjData.h"

class ModelManager
{
public:
	

	static ModelManager* GetInstance();

	static void Initialize();

	static void Finalize();

	static uint32_t LoadObjectFile();


private:

	map<string,SModelData>objModelDatas_;


};


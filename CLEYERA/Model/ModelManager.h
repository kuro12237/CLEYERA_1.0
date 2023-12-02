#pragma once
#include"Pch.h"
#include"ModelObjData.h"
#include"Graphics/TextureManager/TextureManager.h"

class ModelManager
{
public:
	

	static ModelManager* GetInstance();

	static void Initialize();

	static void Finalize();

	static uint32_t LoadObjectFile(string directoryPath);


private:

	static bool ChackLoadObj(string filePath);

	map<string,unique_ptr<ModelObjData>>objModelDatas_;
	uint32_t objHandle_ = 0;

};


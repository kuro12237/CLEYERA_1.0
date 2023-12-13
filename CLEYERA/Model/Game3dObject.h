#pragma once
#include"ModelManager.h"

class Game3dObject
{
public:
	Game3dObject() {};
	~Game3dObject() {};

	void Create();

	void SetModel(uint32_t index);

	void Draw(WorldTransform worldTransform,ViewProjection view);


private:

	Model *model_ = nullptr;

	uint32_t prevIndex_ = 0;

	ComPtr<ID3D12Resource> MaterialBuffer_ = nullptr;
};
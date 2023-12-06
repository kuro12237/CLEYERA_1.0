#pragma once
#include"Light.h"
#include"Graphics/DescripterManager/DescriptorManager.h"

class LightingManager
{
public:
	
	static LightingManager* GetInstance();

	static void Initialize();

	static void AddList(Light* instance);

	static list<Light*> GetLightData();

	static uint32_t dsvHandle() {return LightingManager::GetInstance()->dsvHandle_; }
	static ID3D12Resource* GetBuffer() {return LightingManager::GetInstance()->buffer_.Get();}

	static void TransfarBuffers();

	static uint32_t GetNowLight() {return  LightingManager::GetInstance()->NowTotalLightData_; }


private:

	static void TransfarBuffer();

	static void TransfarStructureBuffer();

	/// <summary>
	/// Lightの合計の数値を送る用
	/// </summary>
	ComPtr<ID3D12Resource>buffer_ = nullptr;

	/// <summary>
	/// ストラクチャーバッファ
	/// </summary>
	ComPtr<ID3D12Resource>structureBuffer_ = nullptr;

	const uint32_t NumLight_ = 10;

	uint32_t NowTotalLightData_ = 0;

	uint32_t dsvHandle_ = 0;

	list<Light*>LightDatas_;

};
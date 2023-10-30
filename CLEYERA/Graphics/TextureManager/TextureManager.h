#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"WinApp.h"
#include"CreateResource.h"
#include"Graphics/DescripterManager/DescriptorManager.h"
#include"Graphics/TextureManager/CreateTextureResource.h"
#define TEXTURE_LOAD_MAX 64


class TextureManager
{
public:
	
	static TextureManager* GetInstance();

	static void Initialize();
	static void Finalize();

	static uint32_t LoadTexture(const std::string& filePath);

private:

	static ComPtr<ID3D12Resource> CreateTexResource(const DirectX::TexMetadata& metadata);

	static DirectX::ScratchImage CreateMipImage(const std::string& filePath);

	static void UploadTexData(const DirectX::ScratchImage& mipImage);

	static D3D12_RESOURCE_DESC SettingResource(const DirectX::TexMetadata& metadata);

	static D3D12_HEAP_PROPERTIES SettingHeap();


	static bool CheckTexDatas(string filePath);

	map<string, unique_ptr<TexDataResource>>texDatas_;

#pragma region 
	//Singleton
	TextureManager() = default;
	~TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	const TextureManager& operator=(const TextureManager&) = delete;
#pragma endregion 
};



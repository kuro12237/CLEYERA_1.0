#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#define DESCRIPTER_MAX 64

struct DescriptorSize
{
	uint32_t SRV;
	uint32_t RTV;
	uint32_t DSV;
};

class DescriptorManager
{
public:

	static DescriptorManager* GetInstance();

	static void Initialize();

	static void BeginFlame();

	static void Clear();

	/// <summary>
	/// InstancingのSRVを作成
	/// </summary>
	static uint32_t CreateInstancingSRV(uint32_t NumInstansing, ComPtr<ID3D12Resource>& resource, UINT size);

	static uint32_t CreateMultipassSrvTexResource(DXGI_FORMAT format, const float clearColor[]);

	/// <summary>
    /// CPUとGPUのptrをずらす
    /// </summary>
	static void CGHandlePtr();

	/// <summary>
	/// indexをインクリメントしてdescripterをずらす
	/// </summary>
	static void IndexIncrement() { DescriptorManager::GetInstance()->index++; }


	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

	static void CreateSRVDescripter(uint32_t index, ID3D12Resource* resource, DXGI_FORMAT format);


#pragma region set

	static void SetCPUDescripterHandle(D3D12_CPU_DESCRIPTOR_HANDLE CpuDescripterHandle, uint32_t index)
	{
		DescriptorManager::GetInstance()->SrvHandleCPU[index] = CpuDescripterHandle;
	}

	static void SetGPUDescripterHandle(D3D12_GPU_DESCRIPTOR_HANDLE GpuDescripterHandle, uint32_t index)
	{
		DescriptorManager::GetInstance()->SrvHandleGPU[index] = GpuDescripterHandle;
	}

#pragma endregion

#pragma region get

	static D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descripterHeap, uint32_t desiripterSize, uint32_t index);

	static D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ComPtr<ID3D12DescriptorHeap> descripterHeap, uint32_t desiripterSize, uint32_t index);
	
	static uint32_t GetIndex() { return DescriptorManager::GetInstance()->index; }

	static DescriptorSize GetDescripterSize() { return DescriptorManager::GetInstance()->descripterSize_; }
#pragma endregion

#pragma region Command

	/// <summary> 
	/// rootParameterのコマンド積む
    /// </summary>
	static void rootParamerterCommand(UINT rootPatramerterIndex, uint32_t texhandle);

	static void CreateShaderResourceView(ID3D12Resource* resource, D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc, uint32_t index);

#pragma endregion
	
private:

	D3D12_CPU_DESCRIPTOR_HANDLE SrvHandleCPU[DESCRIPTER_MAX]{};
	D3D12_GPU_DESCRIPTOR_HANDLE SrvHandleGPU[DESCRIPTER_MAX]{};

	DescriptorSize descripterSize_{};
	uint32_t index = 0;

//Singleton
	DescriptorManager() = default;
	~DescriptorManager() = default;
	DescriptorManager(const DescriptorManager&) = delete;
	const  DescriptorManager& operator=(const DescriptorManager&) = delete;
};






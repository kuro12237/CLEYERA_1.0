#pragma once
#include"DirectXCommon.h"
#include"CreateResource.h"
#include"Graphics/DescripterManager/DescriptorManager.h"

class PeraPolygon
{
public:

	struct Position_Texcoord
	{
		Vector4 pos;
		Vector2 tex;
	};

	PeraPolygon() {};
	~PeraPolygon() {};

	static PeraPolygon* GetInstance();

	static void Initialize();

private:

	static void CreateVertex();
	static void CreateMultiPathDescripterHeap();


	ComPtr<ID3D12Resource>resource_ = nullptr;
	D3D12_VERTEX_BUFFER_VIEW bufferview_{};

	ComPtr<ID3D12DescriptorHeap>m_pPeraRTVHeap = nullptr;
	ComPtr<ID3D12DescriptorHeap>m_pPeraSRVHeap = nullptr;

};


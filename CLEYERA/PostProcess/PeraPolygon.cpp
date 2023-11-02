#include "PeraPolygon.h"

PeraPolygon* PeraPolygon::GetInstance()
{
	static PeraPolygon instance;
	return &instance;
}

void PeraPolygon::Initialize()
{
	CreateVertex();
	CreateMultiPathDescripterHeap();
}

void PeraPolygon::CreateVertex()
{
	//Position_Texcoord PeraBox{};
	const uint32_t PeraBoxMaxSize = 6;
	//1
	//11
	//Position_Texcoord PeraBox_leftBottom = { -1.0f,-1.0f,1.0f,1.0f,0.0f,1.0f };
	//Position_Texcoord PeraBox_leftTop = { -1.0f,1.0f,1.0f,1.0f,0.0f,0.0f };
	//Position_Texcoord PeraBox_rightBottom = { 1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f };
	//PeraBox_leftBottom, PeraBox_leftTop, PeraBox_leftbottom;
	////11
	//// 1
	//Position_Texcoord PeraBox_RigTop = { -1.0f,1.0f,1.0f,1.0f,0.0f,0.0f };
	//Position_Texcoord PeraBox_rightTop = { 1.0f,1.0f,1.0f,1.0f,1.0f,0.0f };
	//Position_Texcoord PeraBox_rightBottom = { 1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f };

	//頂点とBufferViewの作成
	D3D12_HEAP_PROPERTIES uploadHeapProperties{};
	uploadHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;//UploadHeapを使う
	//頂点リソースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	//バッファリソース。テクスチャの場合はまた別の設定をする
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = sizeof(Position_Texcoord);
	//バッファの場合はこれらは１にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	//バッファの場合はこれにする決まり
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
	//実際に頂点リソースを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> resource = nullptr;
	HRESULT hr = DirectXCommon::GetInstance()->GetDevice()->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE,
		&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&resource));
	assert(SUCCEEDED(hr));
	
}

void PeraPolygon::CreateMultiPathDescripterHeap()
{
	D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
	heapDesc.NumDescriptors = 1;
	//MultiPass用のRTV作成
	HRESULT result{};
	result = 
		DirectXCommon::GetInstance()->GetDevice().Get()->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(PeraPolygon::GetInstance()->m_pPeraRTVHeap.ReleaseAndGetAddressOf()));

	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
	rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
	rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

	PeraPolygon::GetInstance()->m_pPeraRTVHeap = DescriptorManager::CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 1, false);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle =
		DirectXCommon::GetInstance()->GetCPUDescriptorHandle(
			PeraPolygon::GetInstance()->m_pPeraRTVHeap,
			DescriptorManager::GetInstance()->GetDescripterSize().RTV, 0
		);
	
	DirectXCommon::GetInstance()->GetDevice().Get()->CreateRenderTargetView(
		PeraPolygon::GetInstance()->resource_.Get(),
		&rtvDesc,
		rtvHandle
	);
	////MultiPass用のSRVを作成
	//heapDesc.NumDescriptors = 1;
	//heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	//heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	//result = DirectXCommon::GetInstance()->GetDevice().Get()->CreateDescriptorHeap(
	//	&heapDesc,
	//	IID_PPV_ARGS(PeraPolygon::GetInstance()->m_pPeraSRVHeap.ReleaseAndGetAddressOf())
	//);

	//D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
	//srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
	//srvDesc.Format = rtvDesc.Format;
	//srvDesc.Texture2D.MipLevels = 1;
	//srvDesc.Shader4ComponentMapping =
	//	D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	//DirectXCommon::GetInstance()->GetDevice().Get()->CreateShaderResourceView(
	//	PeraPolygon::GetInstance()->resource_.Get(),
	//	&srvDesc,
	//	PeraPolygon::GetInstance()->m_pPeraSRVHeap->GetCPUDescriptorHandleForHeapStart()
	//);

}

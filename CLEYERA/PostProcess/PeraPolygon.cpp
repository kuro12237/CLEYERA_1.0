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

void PeraPolygon::PreDraw()
{
	//barrierを張る
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	
	barrier.Transition.pResource = TextureManager::GetInstance()->textursDataResource(0, "peraTex");
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	
	DirectXCommon::GetInstance()->GetCommands().m_pList.Get()->ResourceBarrier(
		1, &barrier);

	auto rtvHeappointer = PeraPolygon::GetInstance()->m_pPeraRTVHeap.Get()->GetCPUDescriptorHandleForHeapStart();
	
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = 
		DirectXCommon::GetInstance()->GetCPUDescriptorHandle(
		DirectXCommon::GetInstance()->GetDsvHeap()
		, DescriptorManager::GetInstance()->GetDescripterSize().DSV, 0);
	

	DirectXCommon::GetInstance()->GetCommands().m_pList.Get()->OMSetRenderTargets(
		2, &rtvHeappointer, false,
		&dsvHandle
	);
	DirectXCommon::GetInstance()->GetCommands().m_pList.Get()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	rtvHandles[0] = DescriptorManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetRtv().m_pDescritorHeap.Get(), DescriptorManager::GetInstance()->GetDescripterSize().RTV, 0);
	rtvHandles[1] = DescriptorManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetRtv().m_pDescritorHeap.Get(), DescriptorManager::GetInstance()->GetDescripterSize().RTV, 1);
	
	float clearColor[] = { 0.1f,0.25f,0.5f,1.0f };
	DirectXCommon::GetInstance()->GetCommands().m_pList.Get()->ClearRenderTargetView(rtvHandles[0], clearColor, 0, nullptr);
	float clearDepthColor[] = { 1.0f,0.0f,0.0f,0.0f };
	DirectXCommon::GetInstance()->GetCommands().m_pList.Get()->ClearRenderTargetView(rtvHandles[1], clearDepthColor, 0, nullptr);
}

void PeraPolygon::PostDraw()
{
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	//通常
	barrier.Transition.pResource = TextureManager::GetInstance()->textursDataResource(0,"peraTex");
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
	DirectXCommon::GetInstance()->GetCommands().m_pList.Get()->ResourceBarrier(1, &barrier);

	//RTV用ディスクリプタヒープのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles[2];
	rtvHandles[0] = DescriptorManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetRtv().m_pDescritorHeap.Get(), DescriptorManager::GetInstance()->GetDescripterSize().RTV, 0);
	rtvHandles[1] = DescriptorManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetRtv().m_pDescritorHeap.Get(), DescriptorManager::GetInstance()->GetDescripterSize().RTV, 1);
	//DSV用ディスクリプターのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = DescriptorManager::GetCPUDescriptorHandle(DirectXCommon::GetInstance()->GetDsvHeap(), DescriptorManager::GetInstance()->GetDescripterSize().DSV, 0);
	//描画先のRTVを設定する

	UINT backBufferIndex = DirectXCommon::GetInstance()->GetswapChain().m_pSwapChain->GetCurrentBackBufferIndex();
	DirectXCommon::GetInstance()->GetCommands().m_pList.Get()->OMSetRenderTargets(1, &rtvHandles[backBufferIndex], false, &dsvHandle);
}

void PeraPolygon::CreateVertex()
{
	Position_Texcoord PeraBox{};
	//const uint32_t PeraBoxMaxSize = 6;
	//1
	//11
	Position_Texcoord PeraBox_leftBottom1 = { -1.0f,-1.0f,1.0f,1.0f,0.0f,1.0f };
	Position_Texcoord PeraBox_leftTop1 = { -1.0f,1.0f,1.0f,1.0f,0.0f,0.0f };
	Position_Texcoord PeraBox_rightBottom1 = { 1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f };
	//PeraBox_leftBottom, PeraBox_leftTop, PeraBox_leftbottom;
	//11
	// 1
	Position_Texcoord PeraBox_RigftTop2 = { -1.0f,1.0f,1.0f,1.0f,0.0f,0.0f };
	Position_Texcoord PeraBox_leftTop2 = { 1.0f,1.0f,1.0f,1.0f,1.0f,0.0f };
	Position_Texcoord PeraBox_rightBottom2 = { 1.0f,-1.0f,1.0f,1.0f,1.0f,1.0f };

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
	heapDesc.NumDescriptors = 1;
	heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;

	result = DirectXCommon::GetInstance()->GetDevice().Get()->CreateDescriptorHeap(
		&heapDesc,
		IID_PPV_ARGS(PeraPolygon::GetInstance()->m_pPeraSRVHeap.ReleaseAndGetAddressOf())
	);

	//srvの確保
	float clearColor[] = { 0.1f,0.25f,0.5f,1.0f };
	uint32_t PeraResourceIndex = TextureManager::CreatePostProsessTex(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB, clearColor,"peraTex");

	PeraResourceIndex;


}

#pragma once
#include"Pch.h"
#include"DirectXCommon.h"
#include"CreateResource.h"
struct  VertexData
{
	Vector4 position;
    Vector2 texcoord;
	Vector3 normal;
};
struct LightData
{
	Vector4 color;
	Vector3 direction;
	float intensity;
};

struct  TransformationViewMatrix
{
	Matrix4x4 view;
	Matrix4x4 viewProjection;
	Matrix4x4 orthographic;
};

struct TransformationMatrix {
	Matrix4x4 WVP;
	Matrix4x4 world;
};

struct ParticleData{
	Matrix4x4 WVP;
	Matrix4x4 world;
	Vector4 color;
	Matrix4x4 uvTransform;
};
struct MaterialData
{
	string textureFilePath;
};

struct  SModelData
{
	vector<VertexData> vertices;
	MaterialData material;
};




struct ResourcePeroperty
{
	D3D12_VERTEX_BUFFER_VIEW BufferView;
	D3D12_INDEX_BUFFER_VIEW IndexBufferView;
	ComPtr<ID3D12Resource> Index;
	ComPtr<ID3D12Resource> Vertex;
	ComPtr<ID3D12Resource> Material;
	ComPtr<ID3D12Resource> wvpResource;
	ComPtr<ID3D12Resource> Light;
	ComPtr<ID3D12Resource> instancingResource;
};

struct  Material
{
	Vector4 color;
	Matrix4x4 uvTransform;
};

class CreateResources
{
public:

	/// <summary>
	/// Resource��쐬
	/// </summary>
	/// <param name="device"></param>
	/// <param name="sizeInbyte"></param>
	/// <returns></returns>
	static ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInbyte);

	/// <summary>
	/// BufferView��쐬
	/// </summary>
	/// <param name="sizeInbyte"></param>
	/// <param name="Resource"></param>
	/// <returns></returns>
	static D3D12_VERTEX_BUFFER_VIEW VertexCreateBufferView(size_t sizeInbyte, ComPtr<ID3D12Resource> Resource, int size);
	/// <summary>
	/// index��BufferView
	/// </summary>
	/// <param name="NumVertex"></param>
	/// <returns></returns>
	static D3D12_INDEX_BUFFER_VIEW IndexCreateBufferView(size_t sizeInbyte, ComPtr<ID3D12Resource> Resource);

private:


};

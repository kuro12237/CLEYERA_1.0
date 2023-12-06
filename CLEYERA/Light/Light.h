#pragma once
#include"Pch.h"
#include"CreateResource.h"

struct PointLight_param
{
	Vector4 color = {1.0f,1.0f,1.0f,1.0f};
	Vector3 position = {0.0f,0.0f,0.0f};
	/// <summary>
	/// 強さ
	/// </summary>
	float intencity = 1.0f;
	/// <summary>
	/// 最大半径
	/// </summary>
	float radious = 1.0f;
	/// <summary>
	/// 減衰率
	/// </summary>
	float decay = 0.1f;
	

};
//
//struct Light
//{
//
//
//	void Initialize();
//
//	void TransfarData();
//
//	void CreateBuffer();
//
//	ComPtr<ID3D12Resource>buffer_ = nullptr;
//	PointLight_param* data_;
//
//	Vector4 color_ = {1,1,1,1};
//	Vector3 position_ = {0,4,0};
//	float intencity_ = 1.0f;
//	float decay_ = 0.1f;
//	float radious_ = 10.0f;
//};
//

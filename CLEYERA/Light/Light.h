#pragma once
#include"Pch.h"
#include"CreateResource.h"

struct PointLight_param
{
	Vector4 color;
	Vector3 position;
	float intencity;

};

struct Light
{


	void Initialize();

	void TransfarData();

	void CreateBuffer();

	ComPtr<ID3D12Resource>buffer_ = nullptr;
	PointLight_param* data_;

	Vector4 color_ = {1,1,1,1};
	Vector3 position_ = {0,4,0};
	float intencity_ = 1.0f;

};


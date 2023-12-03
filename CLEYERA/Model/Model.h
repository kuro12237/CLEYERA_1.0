#pragma once
#include"Pch.h"
#include"Graphics/TextureManager/TextureManager.h"

#include"ModelPlaneState.h"
#include"ModelLineState.h"
#include"ModelSphereState.h"
#include"ModelObjState.h"
#include"ModelCubeState.h"
#include"WorldTransform.h"
#include"ViewProjection.h"

enum SUseLight
{
	NONE,
	LAMBERT,
	HARF_LAMBERT
};

class Model
{
public:
	~Model();
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="state"></param>
	/// <param name="CenterPos"></param>
	/// <param name="size"></param>
	/// <param name="color"></param>
	void CreateModel(IModelState* state, Vector4 CenterPos = { 0,0,0,1 }, float size = { 0.5 }, Vector4 color = { 1,1,1,1 });

	/// <summary>
	/// DrawLine用の初期化
	/// </summary>
	/// <param name="StertPosition"></param>
	/// <param name="EndPosition"></param>
	/// 
	void CreateLine(IModelState* state, Vector4 StertPosition, Vector4 EndPosition, Vector4 Color = { 1,1,1,1 });

	/// <summary>
	/// modelをセット
	/// </summary>
	/// <param name="ModelHandle"></param>
	void SetModel(uint32_t handle);

	void Draw(WorldTransform worldTransform, ViewProjection viewprojection);

	/// <summary>
	/// ライトを使うか？
	/// </summary>
	void UseLight(SUseLight use);


#pragma region Set
	void SetTexHandle(uint32_t texHandle) { texHandle_ = texHandle; }
	void SetUvScale(Vector3 uvScale) { uvScale_ = uvScale; }
	void SetUvRotate(Vector3 uvRotate) { uvRotate_ = uvRotate; }
	void SetUvTranslate(Vector3 uvTranslate) { uvTranslate_ = uvTranslate; }
	void SetColor(Vector4 color) { color_ = color; }
	//void SetBlendMode(BlendMode blendMode) { blendMode_ = blendMode; }

#pragma endregion 

#pragma region Get

	WorldTransform GetWorldTransform() { return worldTransform_; }
	Vector4 GetColor() { return color_; }
	uint32_t GetTexHandle() { return texHandle_; }
	uint32_t GetModelHandle() { return modelHandle_; }

	Vector3 GetuvScale() { return uvScale_; }
	Vector3 GetuvRotate() { return uvRotate_; }
	Vector3 GetuvTranslate() { return uvTranslate_; }

	/// <summary>
	/// GetLineStartPos
	/// </summary>
	Vector4 GetStartPos() { return StartPos_; }
	/// <summary>
	/// GetLineEndPos
	/// </summary>
	Vector4 GetEndPos() { return EndPos_; }

	/// <summary>
	/// GetModelCenterPos
	/// </summary>
	Vector4 GetCenterPos() { return CenterPos_; }
	/// <summary>
	/// GetModelSize
	/// </summary>
	float GetSize() { return size_; }

	/// <summary>
	/// Color変換
	/// </summary>
	static Vector4 ColorConversion(uint32_t rgbaValue);

	
	SUseLight GetUseLight(){return uselight_;}
#pragma endregion 

private:

	Vector4 CenterPos_ = { 0,0,0,1 };
	float size_=1.5f;

	Vector4 StartPos_ = {};
	Vector4 EndPos_ = {};

	Vector4 color_ = { 1,1,1,1 };
	WorldTransform worldTransform_ = {};
	uint32_t texHandle_ = 0;
	uint32_t modelHandle_ = 0;
	
	Vector3 uvScale_ = {1,1,1};
	Vector3 uvRotate_ = {0,0,0};
	Vector3 uvTranslate_ = {0,0,0};

	SUseLight uselight_ = NONE;

	IModelState* state_ = nullptr;
};


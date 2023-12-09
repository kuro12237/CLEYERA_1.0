#pragma once
#include"Model.h"
#include"Collider/ColliderConfig.h"
#include"Collider/AABBCollider.h"
#include "Collider/OBBCollider.h"
#include"Input.h"

class Player : public AABBCollider, public OBBCollider
{
public:
	Player() {};
	~Player() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;


#pragma region Get

	// Rotateの取得
	Vector3 GetRotate() { return this->worldTransform_.rotation; }

	// Sizeの取得
	Vector3 GetSize() override { return this->size_; }

#pragma endregion 

private:

	void SettingColliderAttributeAndMask();

private:

	unique_ptr<Model>model_ = nullptr;

	uint32_t playerObjPath_ = 0;

	WorldTransform worldTransform_ = {};

	Vector3 size_{};

};
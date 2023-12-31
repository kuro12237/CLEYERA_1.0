#pragma once
#include"Model.h"
#include"Collider/ColliderConfig.h"
#include"Collider/AABBCollider.h"
#include "Collider/OBBCollider.h"

class Enemy : public AABBCollider, public OBBCollider
{
public:
	Enemy() {};
	~Enemy() {};

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

	void SettingProperties();

	void SettingColliderAttributeAndMask();

private:

	unique_ptr<Model>model_ = nullptr;

	uint32_t EnemyObjPath_ = 0;

	WorldTransform worldTransform_ = {};

	Vector3 size_{};

};
#pragma once
#include"Model.h"
#include"Collider/ColliderConfig.h"
#include"Collider/AABBCollider.h"
#include "Collider/OBBCollider.h"

class Enemy : public AABBCollider, OBBCollider
{
public:
	Enemy() {};
	~Enemy() {};

	void Initialize();

	void Update();

	void Draw(ViewProjection view);

	Vector3 GetWorldPosition()override;

	void OnCollision(uint32_t id)override;

private:

	void SettingColliderAttributeAndMask();

private:

	unique_ptr<Model>model_ = nullptr;

	WorldTransform worldTransform_ = {};

};
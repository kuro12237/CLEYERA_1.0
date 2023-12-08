#pragma once
#include"Model.h"
#include"Collider/ColliderConfig.h"
#include"Collider/AABBCollider.h"
#include "Collider/OBBCollider.h"
#include"Input.h"

class Player : public AABBCollider, OBBCollider
{
public:
	Player() {};
	~Player() {};

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

	uint32_t playerObjPath_ = 0;

};
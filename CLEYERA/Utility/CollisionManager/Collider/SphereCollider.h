#pragma once
#include"Pch.h"

class SphereCollider {
public:


	float GetRadious() { return radious_; }
	void SetRadious(float radious) { radious_ = radious; }

	virtual Vector3 GetWorldPosition() = 0;
	virtual void OnCollision(uint32_t id) = 0;

	uint32_t GetCollosionAttribute() const { return collisionAttribute_; }
	void SetCollosionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }

	uint32_t GetCollisionMask() const { return CollisionMask_; }
	void SetCollisionMask(uint32_t collisionMask) { CollisionMask_ = collisionMask; }

	void SetId(uint32_t id) { id_ = id; }
	uint32_t GetId() { return id_; }

private:

	uint32_t collisionAttribute_ = 0xffffffff;

	uint32_t CollisionMask_ = 0xffffffff;

	uint32_t id_ = 0xffffffff;

	float radious_ = 0.5f;
};

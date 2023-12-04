#pragma once
#include"./Collider/SphereCollider.h"
#include"Pch.h"
#include "VectorTransform.h"

class CollisionManager {
public:

	void CheckAllCollision();

	void ClliderPush(SphereCollider* collider) { sphereColliders_.push_back(collider); }
	void ClliderClear() { sphereColliders_.clear(); }

private:
	void CheckCollisionPair(SphereCollider* cA, SphereCollider* cB);
	bool CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2);

	std::list<SphereCollider*> sphereColliders_;
};

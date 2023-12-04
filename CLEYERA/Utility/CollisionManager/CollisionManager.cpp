#include"CollisionManager.h"


void CollisionManager::CheckAllCollision()
{
	std::list<SphereCollider*>::iterator itrA = sphereColliders_.begin();

	for (; itrA != sphereColliders_.end(); ++itrA) {

		SphereCollider* colliderA = *itrA;

		std::list<SphereCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != sphereColliders_.end(); ++itrB) {
			SphereCollider* colliderB = *itrB;
		
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::CheckCollisionPair(SphereCollider* cA, SphereCollider* cB) {

	
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) 
	{
		return;
	}
	Vector3 cApos = cA->GetWorldPosition();
	Vector3 cBpos = cB->GetWorldPosition();

	float cAradious = cA->GetRadious();
	float cBradious = cB->GetRadious();

	if (CheckBallCollosion(cApos, cAradious, cBpos, cBradious)) {
		cA->OnCollision(cB->GetId());
		cB->OnCollision(cA->GetId());
	}
}


bool CollisionManager::CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2) {
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = vr1 + vr2;

	bool Flag = false;

	if (resultPos <= (resultRadious * resultRadious)) {
		Flag = true;
	}

	return Flag;
}



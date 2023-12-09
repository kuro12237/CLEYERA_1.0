#include"CollisionManager.h"


void CollisionManager::CheckAllCollision()
{
	std::list<SphereCollider*>::iterator itrA = sphereColliders_.begin();
	std::list<AABBCollider*>::iterator itrC = aabbColliders_.begin();
	std::list<OBBCollider*>::iterator itrE = obbColliders_.begin();
	std::list<SegmentCollider*>::iterator itrG = segmentColliders_.begin();

	// ‹…‚Æ‹…
	for (; itrA != sphereColliders_.end(); ++itrA) {

		SphereCollider* colliderA = *itrA;

		std::list<SphereCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != sphereColliders_.end(); ++itrB) {
			SphereCollider* colliderB = *itrB;
		
			CheckCollisionPair(colliderA, colliderB);
		}
	}

	// AABB‚ÆAABB
	for (; itrC != aabbColliders_.end(); ++itrC) {

		AABBCollider* colliderC = *itrC;

		std::list<AABBCollider*>::iterator itrD = itrC;
		itrD++;
		for (; itrD != aabbColliders_.end(); ++itrD) {
			AABBCollider* colliderD = *itrD;

			CheckCollisionPair(colliderC, colliderD);
		}
	}

	// AABB‚ÆSegment
	for (; itrC != aabbColliders_.end(); ++itrC) {

		AABBCollider* colliderC = *itrC;

		std::list<AABBCollider*>::iterator itrD = itrC;
		itrD++;
		for (; itrD != aabbColliders_.end(); ++itrD) {
			AABBCollider* colliderD = *itrD;

			CheckCollisionPair(colliderC, colliderD);
		}
	}
}

void CollisionManager::CheckCollisionPair(SphereCollider* cA, SphereCollider* cB) {

	
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) 
	{
		return;
	}


	Sphere A = {
		.center = cA->GetWorldPosition(),
		.radius = cA->GetRadius(),
	};
	Sphere B = {
		.center = cB->GetWorldPosition(),
		.radius = cB->GetRadius(),
	};


	if (Collision::IsCollision(A, B)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

void CollisionManager::CheckCollisionPair(AABBCollider* cA, AABBCollider* cB) {

	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	AABB ca = {};
	ca.max = VectorTransform::Add(ca.max, cA->GetWorldPosition());
	ca.min = VectorTransform::Add(ca.min, cA->GetWorldPosition());

	AABB cb = {};
	cb.max = VectorTransform::Add(cb.max, cB->GetWorldPosition());
	cb.min = VectorTransform::Add(cb.min, cB->GetWorldPosition());


	if (Collision::IsCollision(ca, cb)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

void CollisionManager::CheckCollisionPair(AABBCollider* cA, SegmentCollider* cB) {

	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	if (Collision::IsCollision(cA->GetAABB(), cB->GetSegments())) {
		

	}
}

void CollisionManager::CheckCollisionPair(OBBCollider* cA, SegmentCollider* cB) {

	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	/*if (IsCollision(cA->GetOBB(), cB->GetSegments())) {


	}*/
}
//
//void CollisionManager::CheckCollisionPair(OBBCollider* cA, OBBCollider* cB) {
//
//	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
//		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
//	{
//		return;
//	}
//
//	OBB A = SettingOBBProperties(cA);
//	OBB B = SettingOBBProperties(cB);
//
//	if (Collision::IsCollision(A, B)) {
//		cA->OnCollision(cB->GetID());
//		cB->OnCollision(cA->GetID());
//	}
//}
//


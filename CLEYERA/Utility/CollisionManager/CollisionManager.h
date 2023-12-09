#pragma once
#include"./Collider/SphereCollider.h"
#include "./Collider/OBBCollider.h"
#include "./Collider/AABBCollider.h"
#include "./Collider/SegmentCollider.h"
#include"Pch.h"
#include "VectorTransform.h"
#include "MatrixTransform.h"
#include "IsCollision/IsCollision.h"




class CollisionManager {
public:

	void CheckAllCollision();

	void ClliderSpherePush(SphereCollider* collider) { sphereColliders_.push_back(collider); }
	void ClliderAABBPush(AABBCollider* collider) { aabbColliders_.push_back(collider); }
	
	void ClliderClear() 
	{
		sphereColliders_.clear();
		aabbColliders_.clear();
	}

private:

	// �R���W�����y�A
	void CheckCollisionPair(SphereCollider* cA, SphereCollider* cB);
	void CheckCollisionPair(AABBCollider* cA, AABBCollider* cB);
	void CheckCollisionPair(AABBCollider* cA, SegmentCollider* cB);
	void CheckCollisionPair(OBBCollider* cA, SegmentCollider* cB);
	void CheckCollisionPair(OBBCollider* cA, OBBCollider* cB);

	// ���Ƌ�
	void DetectAllCollisionsInSphere2SphereList(std::list<SphereCollider*>::iterator itrA);

	// AABB��AABB
	void DetectAllCollisionsInAABB2AABBList(std::list<AABBCollider*>::iterator itrA);

	// AABB��Segment
	void DetectAllCollisionsInAABBSegmentList(std::list<OBBCollider*>::iterator itrA);

	// OBB��OBB
	void DetectAllCollisionsInOBB2OBBList(std::list<SegmentCollider*>::iterator itrA);


private:

	// �R���C�_�[���X�g
	std::list<SphereCollider*> sphereColliders_;
	std::list<AABBCollider*> aabbColliders_;
	std::list<OBBCollider*> obbColliders_;
	std::list<SegmentCollider*> segmentColliders_;

};


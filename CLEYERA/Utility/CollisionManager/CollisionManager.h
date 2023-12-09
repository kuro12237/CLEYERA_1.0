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

    // -------------------------------------------------------------------------
    // 衝突検出メソッド
    // -------------------------------------------------------------------------
    // 各種コライダー同士の衝突検出メソッド
    // -------------------------------------------------------------------------
    void DetectSphere2SphereList(list<SphereCollider*>::iterator itrA);
    void DetectAABB2AABBList(list<AABBCollider*>::iterator itrA);
    void DetectAABB2SphereList(list<AABBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB);
    void DetectAABB2SegmentList(list<AABBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB);
    void DetectOBB2SphereList(list<OBBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB);
    void DetectOBB2SegmentList(list<OBBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB);
    void DetectOBB2OBBList(list<OBBCollider*>::iterator itrA);


    // -------------------------------------------------------------------------
    // 衝突検出と応答メソッド
    // -------------------------------------------------------------------------
    // 2つのコライダーの衝突検出と応答メソッド
    // -------------------------------------------------------------------------
    void CheckCollisionPair(SphereCollider* cA, SphereCollider* cB);
    void CheckCollisionPair(AABBCollider* cA, AABBCollider* cB);
    void CheckCollisionPair(AABBCollider* cA, SphereCollider* cB);
    void CheckCollisionPair(AABBCollider* cA, SegmentCollider* cB);
    void CheckCollisionPair(OBBCollider* cA, SphereCollider* cB);
    void CheckCollisionPair(OBBCollider* cA, SegmentCollider* cB);
    void CheckCollisionPair(OBBCollider* cA, OBBCollider* cB);

private:

	// コライダーリスト
	list<SphereCollider*> sphereColliders_;
	list<AABBCollider*> aabbColliders_;
	list<OBBCollider*> obbColliders_;
	list<SegmentCollider*> segmentColliders_;

};


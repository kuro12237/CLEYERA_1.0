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
    // �Փˌ��o���\�b�h
    // -------------------------------------------------------------------------
    // �e��R���C�_�[���m�̏Փˌ��o���\�b�h
    // -------------------------------------------------------------------------
    void DetectSphere2SphereList(list<SphereCollider*>::iterator itrA);
    void DetectAABB2AABBList(list<AABBCollider*>::iterator itrA);
    void DetectAABB2SphereList(list<AABBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB);
    void DetectAABB2SegmentList(list<AABBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB);
    void DetectOBB2SphereList(list<OBBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB);
    void DetectOBB2SegmentList(list<OBBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB);
    void DetectOBB2OBBList(list<OBBCollider*>::iterator itrA);


    // -------------------------------------------------------------------------
    // �Փˌ��o�Ɖ������\�b�h
    // -------------------------------------------------------------------------
    // 2�̃R���C�_�[�̏Փˌ��o�Ɖ������\�b�h
    // -------------------------------------------------------------------------
    void CheckCollisionPair(SphereCollider* cA, SphereCollider* cB);
    void CheckCollisionPair(AABBCollider* cA, AABBCollider* cB);
    void CheckCollisionPair(AABBCollider* cA, SphereCollider* cB);
    void CheckCollisionPair(AABBCollider* cA, SegmentCollider* cB);
    void CheckCollisionPair(OBBCollider* cA, SphereCollider* cB);
    void CheckCollisionPair(OBBCollider* cA, SegmentCollider* cB);
    void CheckCollisionPair(OBBCollider* cA, OBBCollider* cB);

private:

	// �R���C�_�[���X�g
	list<SphereCollider*> sphereColliders_;
	list<AABBCollider*> aabbColliders_;
	list<OBBCollider*> obbColliders_;
	list<SegmentCollider*> segmentColliders_;

};


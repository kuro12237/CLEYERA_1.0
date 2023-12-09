#pragma once
#include"./Collider/SphereCollider.h"
#include "./Collider/OBBCollider.h"
#include "./Collider/AABBCollider.h"
#include "./Collider/SegmentCollider.h"
#include"Pch.h"
#include "VectorTransform.h"
#include "MatrixTransform.h"
#include "IsCollision/IsCollision.h"



/* CollisionManager�N���X */
class CollisionManager {

public:

	/// <summary>
	/// �o�^���ꂽ���ׂẴR���C�_�[�ɑ΂��ďՓ˂����o����B
	/// </summary>
	void CheckAllCollision();

    /// <summary>
    /// �e��R���C�_�[�����X�g�ɓo�^���郁�\�b�h
    /// </summary>
    void ColliderSpherePushBack(SphereCollider* collider) { sphereColliders_.push_back(collider); }
    void ColliderSegmentPushBack(SegmentCollider* collider) { segmentColliders_.push_back(collider); }
    void ColliderAABBPushBack(AABBCollider* collider) { aabbColliders_.push_back(collider); }
    void ColliderOBBPushBack(OBBCollider* collider) { obbColliders_.push_back(collider); }

    /// <summary>
    /// �o�^���ꂽ�R���C�_�[���X�g���N���A���郁�\�b�h
    /// </summary>
    void ClliderClear()	{
		sphereColliders_.clear();
        segmentColliders_.clear();
		aabbColliders_.clear();
        obbColliders_.clear();
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
	list<SegmentCollider*> segmentColliders_;
    list<AABBCollider*> aabbColliders_;
    list<OBBCollider*> obbColliders_;
};


#pragma once
#include"./Collider/SphereCollider.h"
#include "./Collider/OBBCollider.h"
#include "./Collider/AABBCollider.h"
#include "./Collider/SegmentCollider.h"
#include"Pch.h"
#include "VectorTransform.h"
#include "MatrixTransform.h"

#include <array>




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

	// ���Ƌ��̏Փ˔���
	bool CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2);


	/// �Փ˔���
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);
	bool IsCollision(const AABB& aabb, const Segment& s);
	bool IsCollision(const OBB& obb, const Segment& s);
	bool IsCollision(const OBB& obb1, const OBB& obb2);

	// OBB�̃��[���h�}�g���b�N�X�쐬
	Matrix4x4 CreateOBBWorldMatrix(const OBB& obb);


	// �ˉe�̏d���`�F�b�N
	bool TestAxis(const Vector3& axis, const OBB& obb1, const OBB& obb2);

	// ���ۂɏd�Ȃ��Ă邩�̌v�Z
	bool projectionOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2);

	// ���_�����Ɏˉe
	std::pair<float, float> obbProjection(const OBB& obb, const Vector3& axis);

	// OBB�̐ݒ�
	OBB SettingOBBProperties(OBBCollider* c);


private:

	// �R���C�_�[���X�g
	std::list<SphereCollider*> sphereColliders_;
	std::list<AABBCollider*> aabbColliders_;
	std::list<OBBCollider*> obbColliders_;
	std::list<SegmentCollider*> segmentColliders_;

};


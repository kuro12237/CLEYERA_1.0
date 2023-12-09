#include"CollisionManager.h"



// �Փ˔���
void CollisionManager::CheckAllCollision()
{

	std::list<SphereCollider*>::iterator itrSpherre = sphereColliders_.begin();
	std::list<SegmentCollider*>::iterator itrSegment = segmentColliders_.begin();
	std::list<AABBCollider*>::iterator itrAABB = aabbColliders_.begin();
	std::list<OBBCollider*>::iterator itrOBB = obbColliders_.begin();

	// push_back���ĂȂ��̂ŁA��񂪓����ĂȂ�
	// ���̏�ԂŏՓ˔��肷��ƃG���[�͂���
	// ��ŏ����̒���if������āA���͌����ĂȂ������甲����悤�ɂ���


	/* �e��R���C�_�[���m�̏Փˌ��o���\�b�h */
	// Sphere��Sphere
	//DetectSphere2SphereList(itrSpherre);
	// AABB��AABB
	DetectAABB2AABBList(itrAABB);
	// AABB��Sphere
	//(itrAABB, itrSpherre);
	// AABB��Segment
	//DetectAABB2SegmentList(itrAABB, itrSegment);
	// OBB��Sphere
	//DetectOBB2SphereList(itrOBB, itrSpherre);
	// OBB��Segmetn
	//DetectOBB2SegmentList(itrOBB, itrSegment);
	// OBB��OBB
	//DetectOBB2OBBList(itrOBB);
}



/// <summary>
/// �Փˌ��o���\�b�h : Sphere2Sphere
/// </summary>
void CollisionManager::DetectSphere2SphereList(list<SphereCollider*>::iterator itr1) {

	for (; itr1 != sphereColliders_.end(); ++itr1) {

		SphereCollider* colliderA = *itr1;

		list<SphereCollider*>::iterator itr2 = itr1;
		itr2++;
		for (; itr2 != sphereColliders_.end(); ++itr2) {
			SphereCollider* colliderB = *itr2;

			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

/// <summary>
/// �Փˌ��o���\�b�h : AABB2AABB
/// </summary>
void CollisionManager::DetectAABB2AABBList(list<AABBCollider*>::iterator itrA) {

	for (; itrA != aabbColliders_.end(); ++itrA) {

		AABBCollider* colliderA= *itrA;

		list<AABBCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != aabbColliders_.end(); ++itrB) {
			AABBCollider* colliderB = *itrB;

			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

/// <summary>
/// �Փˌ��o���\�b�h : AABB2Sphere
/// </summary>
void CollisionManager::DetectAABB2SphereList(list<AABBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB) {

	for (; itrA != aabbColliders_.end(); ++itrA) {

		AABBCollider* colliderA = *itrA;

		list<SphereCollider*>::iterator newItrB = itrB;
		newItrB++;
		for (; newItrB != sphereColliders_.end(); ++newItrB) {
			SphereCollider* colliderB = *newItrB;

			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

/// <summary>
/// �Փˌ��o���\�b�h : AABB2Segment
/// </summary>
void CollisionManager::DetectAABB2SegmentList(list<AABBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB) {

	for (; itrA != aabbColliders_.end(); ++itrA) {

		AABBCollider* colliderA = *itrA;

		list<SegmentCollider*>::iterator newItrB = itrB;
		newItrB++;
		for (; newItrB != segmentColliders_.end(); ++newItrB) {
			SegmentCollider* colliderB = *newItrB;

			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

/// <summary>
/// �Փˌ��o���\�b�h : OBB2Sphere
/// </summary>
void CollisionManager::DetectOBB2SphereList(list<OBBCollider*>::iterator itrA, list<SphereCollider*>::iterator itrB) {

	for (; itrA != obbColliders_.end(); ++itrA) {

		OBBCollider* colliderA = *itrA;

		list<SphereCollider*>::iterator newItrB = itrB;
		newItrB++;
		for (; newItrB != sphereColliders_.end(); ++newItrB) {
			SphereCollider* colliderB = *newItrB;

			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

/// <summary>
/// �Փˌ��o���\�b�h : OBB2Segment
/// </summary>
void CollisionManager::DetectOBB2SegmentList(list<OBBCollider*>::iterator itrA, list<SegmentCollider*>::iterator itrB) {

	for (; itrA != obbColliders_.end(); ++itrA) {

		OBBCollider* colliderA = *itrA;

		list<SegmentCollider*>::iterator newItrB = itrB;
		newItrB++;
		for (; newItrB != segmentColliders_.end(); ++newItrB) {
			SegmentCollider* colliderB = *newItrB;

			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

/// <summary>
/// �Փˌ��o���\�b�h : OBB2OBB
/// </summary>
void CollisionManager::DetectOBB2OBBList(list<OBBCollider*>::iterator itrA) {

	for (; itrA != obbColliders_.end(); ++itrA) {

		OBBCollider* colliderA = *itrA;

		list<OBBCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != obbColliders_.end(); ++itrB) {
			OBBCollider* colliderB = *itrB;

			CheckCollisionPair(colliderA, colliderB);
		}
	}
}




/// <summary>
/// 2�̃R���C�_�[�̏Փˌ��o�Ɖ������\�b�h
///  : Sphere2Sphere
/// </summary>
void CollisionManager::CheckCollisionPair(SphereCollider* cA, SphereCollider* cB) {

	// �R���W�����t�B���^�����O
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) 
	{
		return;
	}

	// �l����ꂽ�\���̂����
	Sphere SphereA = {
		.center = cA->GetWorldPosition(),
		.radius = cA->GetRadius(),
	};
	Sphere SphereB = {
		.center = cB->GetWorldPosition(),
		.radius = cB->GetRadius(),
	};

	// �Փ˔���
	if (Collision::IsCollision(SphereA, SphereB)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

/// <summary>
/// 2�̃R���C�_�[�̏Փˌ��o�Ɖ������\�b�h
///  : AABB2AABB
/// </summary>
void CollisionManager::CheckCollisionPair(AABBCollider* cA, AABBCollider* cB) {

	// �R���W�����t�B���^�����O
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	// �l����ꂽ�\���̂����
	AABB aabbA = SettingAABBProperties(cA);
	AABB aabbB = SettingAABBProperties(cB);

	// �Փ˔���
	if (Collision::IsCollision(aabbA, aabbB)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

/// <summary>
/// 2�̃R���C�_�[�̏Փˌ��o�Ɖ������\�b�h
///  : AABB2Sphere
/// </summary>
void CollisionManager::CheckCollisionPair(AABBCollider* cA, SphereCollider* cB) {

	// �R���W�����t�B���^�����O
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	// �l����ꂽ�\���̂����
	AABB aabb = SettingAABBProperties(cA);
	Sphere sphere = {
		.center = cB->GetWorldPosition(),
		.radius = cB->GetRadius(),
	};

	// �Փ˔���
	if (Collision::IsCollision(aabb, sphere)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

/// <summary>
/// 2�̃R���C�_�[�̏Փˌ��o�Ɖ������\�b�h
///  : AABB2Segment
/// </summary>
void CollisionManager::CheckCollisionPair(AABBCollider* cA, SegmentCollider* cB) {

	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	/*if (Collision::IsCollision(cA->GetAABB(), cB->GetSegments())) {
		

	}*/
}

/// <summary>
/// 2�̃R���C�_�[�̏Փˌ��o�Ɖ������\�b�h
///  : OBB2Sphere
/// </summary>
void CollisionManager::CheckCollisionPair(OBBCollider* cA, SphereCollider* cB) {

	// �R���W�����t�B���^�����O
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	// �l����ꂽ�\���̂����
	OBB obb = SettingOBBProperties(cA);
	Sphere sphere = {
		.center = cB->GetWorldPosition(),
		.radius = cB->GetRadius(),
	};

	// �Փ˔���
	if (Collision::IsCollision(obb, sphere)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

/// <summary>
/// 2�̃R���C�_�[�̏Փˌ��o�Ɖ������\�b�h
///  : OBB2Segment
/// </summary>
void CollisionManager::CheckCollisionPair(OBBCollider* cA, SegmentCollider* cB) {

	// �R���W�����t�B���^�����O
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	//// �l����ꂽ�\���̂����
	//OBB obb = SettingOBBProperties(cA);
	//Segment segment = {};

	//// �Փ˔���
	//if (Collision::IsCollision(obb, segment)) {
	//	cA->OnCollision(cB->GetID());
	//	cB->OnCollision(cA->GetID());
	//}
}

/// <summary>
/// 2�̃R���C�_�[�̏Փˌ��o�Ɖ������\�b�h
///  : OBB2OBB
/// </summary>
void CollisionManager::CheckCollisionPair(OBBCollider* cA, OBBCollider* cB) {

	// �R���W�����t�B���^�����O
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	// �l����ꂽ�\���̂����
	OBB obbA = SettingOBBProperties(cA);
	OBB obbB = SettingOBBProperties(cB);

	// �Փ˔���
	if (Collision::IsCollision(obbA, obbB)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}
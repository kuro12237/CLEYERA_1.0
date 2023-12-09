#pragma once
#include"Pch.h"
#include "CollisionStructures/CollisionStructures.h"


class SegmentCollider {
public:

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	virtual void OnCollision(uint32_t id) = 0;

	/// <summary>
	/// ���[���h���W�̎擾
	/// </summary>
	virtual Vector3 GetWorldPosition() = 0;

#pragma region Segment

	/// <summary>
	/// Radius�̎擾
	/// </summary>
	Segment GetSegments() { return segment_; }

	/// <summary>
	/// Radius�̐ݒ�
	/// </summary>
	void SetRadius(Segment segment) { segment_ = segment; }

#pragma endregion 

#pragma region ID

	/// <summary>
	/// ID�̎擾
	/// </summary>
	uint32_t GetID() { return id_; }

	/// <summary>
	/// ID�̐ݒ�
	/// </summary>
	void SetID(uint32_t id) { id_ = id; }

#pragma endregion 

#pragma region CollisionAttribute

	/// <summary>
	/// collisionAttribute�̎擾
	/// </summary>
	uint32_t GetCollosionAttribute() const { return collisionAttribute_; }

	/// <summary>
	/// collisionAttribute�̐ݒ�
	/// </summary>
	void SetCollosionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }

#pragma endregion

#pragma region CollisionMask

	/// <summary>
	/// CollisionMask�̎擾
	/// </summary>
	uint32_t GetCollisionMask() const { return CollisionMask_; }

	/// <summary>
	/// CollisionMask�̐ݒ�
	/// </summary>
	void SetCollisionMask(uint32_t collisionMask) { CollisionMask_ = collisionMask; }

#pragma endregion

private:

	uint32_t collisionAttribute_ = 0xffffffff;

	uint32_t CollisionMask_ = 0xffffffff;

	uint32_t id_ = 0xffffffff;

	Segment segment_{};
};

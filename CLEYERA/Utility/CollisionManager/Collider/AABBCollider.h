#pragma once


#include "Pch.h"



// AABB
struct AABB {
	Vector3 min = {-0.5f,-0.5f,-0.5f}; // !< �ŏ��_
	Vector3 max = {0.5f,0.5f,0.5f}; // !< �ő�_
};



class AABBCollider {

public:

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	virtual void OnCollision(uint32_t id) = 0;

	/// <summary>
	/// ���[���h���W�̎擾
	/// </summary>
	virtual Vector3 GetWorldPosition() = 0;

#pragma region AABB

	/// <summary>
	/// OBB�̎擾
	/// </summary>
	AABB GetAABB() { return aabb_; }

	/// <summary>
	/// OBB�̐ݒ�
	/// </summary>
	void SetAABB(AABB aabb) { aabb_ = aabb; }

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

	AABB aabb_{};

	uint32_t id_ = 0xffffffff;

	uint32_t collisionAttribute_ = 0xffffffff;

	uint32_t CollisionMask_ = 0xffffffff;
};
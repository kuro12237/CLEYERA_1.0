#pragma once

#include "Pch.h"


// OBB
struct OBB {
	Vector3 center;			   // !< 中心点
	Vector3 orientations[3]{}; // !< 座標軸。正規化・直交必須
	Vector3 size;			   // !< 座標軸方向の長さの半分。中心から面までの距離
};

class OBBCollider {

public:

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	virtual void OnCollision(uint32_t id) = 0;

	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	virtual Vector3 GetWorldPosition() = 0;

#pragma region Size

	/// <summary>
	/// OBBの取得
	/// </summary>
	Vector3 GetSize() { return size_; }

	/// <summary>
	/// OBBの設定
	/// </summary>
	void SetSize(Vector3 size) { size_ = size; }

#pragma endregion 

#pragma region ID

	/// <summary>
	/// IDの取得
	/// </summary>
	uint32_t GetID() { return id_; }

	/// <summary>
	/// IDの設定
	/// </summary>
	void SetID(uint32_t id) { id_ = id; }

#pragma endregion 

#pragma region CollisionAttribute

	/// <summary>
	/// collisionAttributeの取得
	/// </summary>
	uint32_t GetCollosionAttribute() const { return collisionAttribute_; }

	/// <summary>
	/// collisionAttributeの設定
	/// </summary>
	void SetCollosionAttribute(uint32_t collisionAttribute) { collisionAttribute_ = collisionAttribute; }

#pragma endregion

#pragma region CollisionMask

	/// <summary>
	/// CollisionMaskの取得
	/// </summary>
	uint32_t GetCollisionMask() const { return CollisionMask_; }

	/// <summary>
	/// CollisionMaskの設定
	/// </summary>
	void SetCollisionMask(uint32_t collisionMask) { CollisionMask_ = collisionMask; }

#pragma endregion


private:

	OBB obb_{};

	uint32_t id_ = 0xffffffff;

	uint32_t collisionAttribute_ = 0xffffffff;

	uint32_t CollisionMask_ = 0xffffffff;

	Vector3 size_ = { 1.0f, 1.0f ,1.0f };
};
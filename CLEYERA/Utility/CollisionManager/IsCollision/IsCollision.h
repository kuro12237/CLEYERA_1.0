#pragma once

#include"Pch.h"
#include "VectorTransform.h"
#include "MatrixTransform.h"
#include "CollisionStructures/CollisionStructures.h"
#include "GeometryCollision/GeometryCollision.h"
using namespace GeometryCollision;


namespace Collision {

	// ���Ƌ��̓����蔻��
	bool IsCollision(const Sphere& s1, const Sphere& s2);

	// AABB��AABB�̓����蔻��
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	// AABB�Ƌ��̓����蔻��
	bool IsCollision(const AABB& aabb, const Sphere& s);

	// AABB�Ɛ��̓����蔻��
	bool IsCollision(const AABB& aabb, const Segment& s);

	// OBB�Ƌ��̓����蔻��
	bool IsCollision(const OBB& obb, const Sphere& s);

	// OBB�Ɛ��̓����蔻��
	bool IsCollision(const OBB& obb, const Segment& s);

	// OBB��OBB�̓����蔻��
	bool IsCollision(const OBB& obb1, const OBB& obb2);
}
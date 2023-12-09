#pragma once

#include"Pch.h"
#include "VectorTransform.h"
#include "MatrixTransform.h"
#include "CollisionStructures/CollisionStructures.h"
#include "./Collider/OBBCollider.h"
#include "./Collider/AABBCollider.h"

#include <array>


namespace GeometryCollision {

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

	// AABB�̐ݒ�
	AABB SettingAABBProperties(AABBCollider* c);
}
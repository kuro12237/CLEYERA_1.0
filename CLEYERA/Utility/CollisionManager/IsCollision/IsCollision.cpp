#include "IsCollision.h"



namespace Collision {

	// ���Ƌ��̓����蔻��
	bool IsCollision(const Sphere& s1, const Sphere& s2) {

		// ���S����̋���
		float distance = VectorTransform::Length(VectorTransform::Subtruct(s2.center, s1.center));

		// �����Ɣ��a���ׂ�
		if (distance <= s1.radius + s2.radius) {

			// �������Ă�
			return true;
		}
		// �������ĂȂ�
		return false;
	}


	// AABB��AABB�̓����蔻��
	bool IsCollision(const AABB& aabb1, const AABB& aabb2) {

		if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
			(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
			(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
			) {

			// �������Ă���
			return true;
		}
		// �������ĂȂ�
		return false;
	}


	// AABB�Ƌ��̓����蔻��
	bool IsCollision(const AABB& aabb, const Sphere& s) {

		// �ŋߐړ_�����߂�
		const Vector3 ClosestPoint = {
			std::clamp(s.center.x, aabb.min.x, aabb.max.x),
			std::clamp(s.center.y, aabb.min.y, aabb.max.y),
			std::clamp(s.center.z, aabb.min.z, aabb.max.z), };

		// �ŋߐړ_�Ƌ��̒��S�Ƌ��������߂�
		float dist = VectorTransform::Length(VectorTransform::Subtruct(ClosestPoint, s.center));

		// ���������a������������ΏՓ�
		if (dist <= s.radius) {

			// �������Ă�
			return true;
		}
		else {
			// �������ĂȂ�
			return false;
		}
	}


	// AABB�Ɛ��̓����蔻��
	bool IsCollision(const AABB& aabb, const Segment& s) {

		Vector3 tMin = {
		.x = (aabb.min.x - s.origin.x) / s.diff.x,
		.y = (aabb.min.y - s.origin.y) / s.diff.y,
		.z = (aabb.min.z - s.origin.z) / s.diff.z,
		};
		Vector3 tMax = {
			.x = (aabb.max.x - s.origin.x) / s.diff.x,
			.y = (aabb.max.y - s.origin.y) / s.diff.y,
			.z = (aabb.max.z - s.origin.z) / s.diff.z,
		};


		if (std::isnan(tMin.x) || std::isnan(tMax.x) ||
			std::isnan(tMin.y) || std::isnan(tMax.y) ||
			std::isnan(tMin.z) || std::isnan(tMax.z)) {
			return true;
		}


		Vector3 tNear = {
			.x = min(tMin.x, tMax.x),
			.y = min(tMin.y, tMax.y),
			.z = min(tMin.z, tMax.z),
		};
		Vector3 tFar = {
			.x = max(tMin.x, tMax.x),
			.y = max(tMin.y, tMax.y),
			.z = max(tMin.z, tMax.z),
		};

		// AABB�Ƃ̏Փ˓_(�ђʓ_)��t���������ق�
		float ntMin = max(max(tNear.x, tNear.y), tNear.z);
		// AABB�Ƃ̏Փ˓_(�ђʓ_)��t���傫���ق�
		float ntMax = min(min(tFar.x, tFar.y), tFar.z);


		if (ntMin < 0.0f && ntMax < 0.0f || ntMin > 1.0f && ntMax > 1.0f) {
			return false;
		}

		if (ntMin < ntMax) {

			// �������Ă�
			return true;
		}
		else {

			// �������ĂȂ�
			return false;
		}
	}


	// OBB�Ƌ��̓����蔻��
	bool IsCollision(const OBB& obb, const Sphere& s) {

		Vector3 centerInOBBLocalSpace = {
		VectorTransform::TransformByMatrix(
			s.center, MatrixTransform::Inverse(CreateOBBWorldMatrix(obb))) };

		AABB abbOBBLocal = {
			.min = { -obb.halfSize.x, -obb.halfSize.y, -obb.halfSize.z },
			.max = { obb.halfSize.x, obb.halfSize.y, obb.halfSize.z }
		};
		Sphere sphereOBBLocal = {
			centerInOBBLocalSpace,
			s.radius
		};

		// ���[�J�����W�ŏՓ˔���
		if (Collision::IsCollision(abbOBBLocal, sphereOBBLocal)) {

			// �������Ă�
			return true;
		}
		else {

			// �������ĂȂ�
			return false;
		}

	}

	// OBB�Ɛ��̓����蔻��
	bool IsCollision(const OBB& obb, const Segment& s) {

		Matrix4x4 obbInverse = MatrixTransform::Inverse(CreateOBBWorldMatrix(obb));

		AABB aabbOBBLocal = {
			.min = { -obb.halfSize.x, -obb.halfSize.y, -obb.halfSize.z },
			.max = { obb.halfSize.x, obb.halfSize.y, obb.halfSize.z }
		};


		Vector3 localOrigin = VectorTransform::TransformByMatrix(s.origin, obbInverse);
		Vector3 LocalEnd = VectorTransform::TransformByMatrix(VectorTransform::Add(s.origin, s.diff), obbInverse);

		Segment localSegment = {
			.origin = localOrigin,
			.diff = VectorTransform::Subtruct(LocalEnd, localOrigin),
		};


		// AABB��Segment�̓����蔻����g��
		if (IsCollision(aabbOBBLocal, localSegment)) {

			// �������Ă�
			return true;
		}
		else {

			// �������ĂȂ�
			return false;
		}
	}


	// OBB��OBB�̓����蔻��
	bool IsCollision(const OBB& obb1, const OBB& obb2) {

		// �������e�X�g
		for (const auto& axis : obb1.orientations) {
			if (!TestAxis(axis, obb1, obb2)) {
				return false;
			}
		}

		for (const auto& axis : obb2.orientations) {
			if (!TestAxis(axis, obb1, obb2)) {
				return false;
			}
		}

		// OBB1�̎���OBB2�̎��ɐ����Ȏ����e�X�g
		for (const auto& axis : {
				Vector3{obb1.orientations[1].x * obb2.orientations[2].x - obb1.orientations[2].x * obb2.orientations[1].x,
						obb1.orientations[1].y * obb2.orientations[2].y - obb1.orientations[2].y * obb2.orientations[1].y,
						obb1.orientations[1].z * obb2.orientations[2].z - obb1.orientations[2].z * obb2.orientations[1].z},
				Vector3{obb1.orientations[2].x * obb2.orientations[0].x - obb1.orientations[0].x * obb2.orientations[2].x,
						obb1.orientations[2].y * obb2.orientations[0].y - obb1.orientations[0].y * obb2.orientations[2].y,
						obb1.orientations[2].z * obb2.orientations[0].z - obb1.orientations[0].z * obb2.orientations[2].z},
				Vector3{obb1.orientations[0].x * obb2.orientations[1].x - obb1.orientations[1].x * obb2.orientations[0].x,
						obb1.orientations[0].y * obb2.orientations[1].y - obb1.orientations[1].y * obb2.orientations[0].y,
						obb1.orientations[0].z * obb2.orientations[1].z - obb1.orientations[1].z * obb2.orientations[0].z} }) {
			if (!TestAxis(axis, obb1, obb2)) {
				return false;
			}
		}

		return true;
	}
}
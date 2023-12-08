#include"CollisionManager.h"


void CollisionManager::CheckAllCollision()
{
	std::list<SphereCollider*>::iterator itrA = sphereColliders_.begin();
	std::list<AABBCollider*>::iterator itrC = aabbColliders_.begin();
	std::list<OBBCollider*>::iterator itrE = obbColliders_.begin();
	std::list<SegmentCollider*>::iterator itrG = segmentColliders_.begin();

	// 球と球
	for (; itrA != sphereColliders_.end(); ++itrA) {

		SphereCollider* colliderA = *itrA;

		std::list<SphereCollider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != sphereColliders_.end(); ++itrB) {
			SphereCollider* colliderB = *itrB;
		
			CheckCollisionPair(colliderA, colliderB);
		}
	}

	// AABBとAABB
	for (; itrC != aabbColliders_.end(); ++itrC) {

		AABBCollider* colliderC = *itrC;

		std::list<AABBCollider*>::iterator itrD = itrC;
		itrD++;
		for (; itrD != aabbColliders_.end(); ++itrD) {
			AABBCollider* colliderD = *itrD;

			CheckCollisionPair(colliderC, colliderD);
		}
	}

	// AABBとSegment
	for (; itrC != aabbColliders_.end(); ++itrC) {

		AABBCollider* colliderC = *itrC;

		std::list<AABBCollider*>::iterator itrD = itrC;
		itrD++;
		for (; itrD != aabbColliders_.end(); ++itrD) {
			AABBCollider* colliderD = *itrD;

			CheckCollisionPair(colliderC, colliderD);
		}
	}
}

void CollisionManager::CheckCollisionPair(SphereCollider* cA, SphereCollider* cB) {

	
	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0) 
	{
		return;
	}
	Vector3 cApos = cA->GetWorldPosition();
	Vector3 cBpos = cB->GetWorldPosition();

	float cAradious = cA->GetRadius();
	float cBradious = cB->GetRadius();

	if (CheckBallCollosion(cApos, cAradious, cBpos, cBradious)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

void CollisionManager::CheckCollisionPair(AABBCollider* cA, AABBCollider* cB) {

	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	AABB ca = {};
	ca.max = VectorTransform::Add(ca.max, cA->GetWorldPosition());
	ca.min = VectorTransform::Add(ca.min, cA->GetWorldPosition());

	AABB cb = {};
	cb.max = VectorTransform::Add(cb.max, cB->GetWorldPosition());
	cb.min = VectorTransform::Add(cb.min, cB->GetWorldPosition());


	if (IsCollision(ca, cb)) {
		cA->OnCollision(cB->GetID());
		cB->OnCollision(cA->GetID());
	}
}

void CollisionManager::CheckCollisionPair(AABBCollider* cA, SegmentCollider* cB) {

	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
	{
		return;
	}

	if (IsCollision(cA->GetAABB(), cB->GetSegments())) {
		

	}
}
//
//void CollisionManager::CheckCollisionPair(OBBCollider* cA, SegmentCollider* cB) {
//
//	if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
//		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
//	{
//		return;
//	}
//
//	if (IsCollision(cA->GetOBB(), cB->GetSegments())) {
//
//
//	}
//}

//void CollisionManager::CheckCollisionPair(OBBCollider* cA, OBBCollider* cB) {
//
//	/*if ((cA->GetCollosionAttribute() & cB->GetCollisionMask()) == 0 ||
//		(cA->GetCollisionMask() & cB->GetCollosionAttribute()) == 0)
//	{
//		return;
//	}
//
//	if (IsCollision(cA->GetOBB(), cB->GetOBB())) {
//
//
//	}*/
//}



bool CollisionManager::CheckBallCollosion(Vector3 v1, float vr1, Vector3 v2, float vr2) {
	float x = (v2.x - v1.x);
	float y = (v2.y - v1.y);
	float z = (v2.z - v1.z);

	float resultPos = (x * x) + (y * y) + (z * z);

	float resultRadious = vr1 + vr2;

	bool Flag = false;

	if (resultPos <= (resultRadious * resultRadious)) {
		Flag = true;
	}

	return Flag;
}

// 衝突判定
bool CollisionManager::IsCollision(const AABB& aabb1, const AABB& aabb2) {

	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)
		) {

		// 当たっている
		return true;
	}
	// 当たってない
	return false;
}

bool CollisionManager::IsCollision(const AABB& aabb, const Segment& s) {

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

	// AABBとの衝突点(貫通点)のtが小さいほう
	float ntMin = max(max(tNear.x, tNear.y), tNear.z);
	// AABBとの衝突点(貫通点)のtが大きいほう
	float ntMax = min(min(tFar.x, tFar.y), tFar.z);


	if (ntMin < 0.0f && ntMax < 0.0f || ntMin > 1.0f && ntMax > 1.0f) {
		return false;
	}

	if (ntMin < ntMax) {

		// 当たってる
		return true;
	}
	else {

		// 当たってない
		return false;
	}
}

bool CollisionManager::IsCollision(const OBB& obb, const Segment& s) {

	Matrix4x4 obbInverse = MatrixTransform::Inverse(CreateOBBWorldMatrix(obb));

	AABB aabbOBBLocal = {
		.min = { -obb.size.x, -obb.size.y, -obb.size.z },
		.max = { obb.size.x, obb.size.y, obb.size.z }
	};


	Vector3 localOrigin = VectorTransform::TransformByMatrix(s.origin, obbInverse);
	Vector3 LocalEnd = VectorTransform::TransformByMatrix(VectorTransform::Add(s.origin, s.diff), obbInverse);

	Segment localSegment = {
		.origin = localOrigin,
		.diff = VectorTransform::Subtruct(LocalEnd, localOrigin),
	};


	// AABBとSegmentの当たり判定を使う
	if (IsCollision(aabbOBBLocal, localSegment)) {

		// 当たってる
		return true;
	}
	else {

		// 当たってない
		return false;
	}
}

bool CollisionManager::IsCollision(const OBB& obb1, const OBB& obb2) {

	// 分離軸テスト
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

	// OBB1の軸とOBB2の軸に垂直な軸をテスト
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


Matrix4x4 CollisionManager::CreateOBBWorldMatrix(const OBB& obb) {

	Matrix4x4 worldMatrix{};

	for (int i = 0; i < 3; ++i) {
		worldMatrix.m[i][0] = obb.orientations[i].x;
		worldMatrix.m[i][1] = obb.orientations[i].y;
		worldMatrix.m[i][2] = obb.orientations[i].z;
		worldMatrix.m[i][3] = 0.0f;
	}

	worldMatrix.m[3][0] = obb.center.x;
	worldMatrix.m[3][1] = obb.center.y;
	worldMatrix.m[3][2] = obb.center.z;
	worldMatrix.m[3][3] = 1.0f;


	return worldMatrix;
}



// 射影の重複チェック
bool CollisionManager::TestAxis(const Vector3& axis, const OBB& obb1, const OBB& obb2) {

	// OBBの射影を計算
	auto projection1 = obbProjection(obb1, axis);
	auto projection2 = obbProjection(obb2, axis);

	// 射影が重なっているかチェック
	return projectionOverlap(projection1, projection2);
}


// 頂点を軸に射影
std::pair<float, float> CollisionManager::obbProjection(const OBB& obb, const Vector3& axis) {

	float val = std::sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z); // 正規化
	float newAxis = 0.0f;
	newAxis = newAxis / val;

	// OBB上の頂点を取得
	std::array<Vector3, 8> vertices{};
	for (int i = 0; i < 8; ++i) {
		Vector3 sign = { (i & 1) ? 1.0f : -1.0f, (i & 2) ? 1.0f : -1.0f, (i & 4) ? 1.0f : -1.0f };
		vertices[i] = {
			obb.center.x + obb.orientations[0].x * sign.x * obb.size.x +
						  obb.orientations[1].x * sign.y * obb.size.y +
						  obb.orientations[2].x * sign.z * obb.size.z,
			obb.center.y + obb.orientations[0].y * sign.x * obb.size.x +
						  obb.orientations[1].y * sign.y * obb.size.y +
						  obb.orientations[2].y * sign.z * obb.size.z,
			obb.center.z + obb.orientations[0].z * sign.x * obb.size.x +
						  obb.orientations[1].z * sign.y * obb.size.y +
						  obb.orientations[2].z * sign.z * obb.size.z
		};
	}

	// 頂点を軸に射影
	std::array<float, 8> projections{};
	for (int i = 0; i < 8; ++i) {
		projections[i] = vertices[i].x * axis.x + vertices[i].y * axis.y + vertices[i].z * axis.z;
	}

	auto minmax = std::minmax_element(projections.begin(), projections.end());
	return std::make_pair(*minmax.first, *minmax.second);
}


// 実際に重なってるかの計算
bool CollisionManager::projectionOverlap(const std::pair<float, float>& projection1, const std::pair<float, float>& projection2) {

	// 射影が重なっているかチェック
	return projection1.second >= projection2.first && projection2.second >= projection1.first;
}




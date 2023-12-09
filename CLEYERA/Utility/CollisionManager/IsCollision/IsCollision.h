#pragma once

#include"Pch.h"
#include "VectorTransform.h"
#include "MatrixTransform.h"
#include "CollisionStructures/CollisionStructures.h"
#include "GeometryCollision/GeometryCollision.h"
using namespace GeometryCollision;


namespace Collision {

	// ‹…‚Æ‹…‚Ì“–‚½‚è”»’è
	bool IsCollision(const Sphere& s1, const Sphere& s2);

	// AABB‚ÆAABB‚Ì“–‚½‚è”»’è
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	// AABB‚Æ‹…‚Ì“–‚½‚è”»’è
	bool IsCollision(const AABB& aabb, const Sphere& s);

	// AABB‚Æü‚Ì“–‚½‚è”»’è
	bool IsCollision(const AABB& aabb, const Segment& s);

	// OBB‚Æ‹…‚Ì“–‚½‚è”»’è
	bool IsCollision(const OBB& obb, const Sphere& s);

	// OBB‚Æü‚Ì“–‚½‚è”»’è
	bool IsCollision(const OBB& obb, const Segment& s);

	// OBB‚ÆOBB‚Ì“–‚½‚è”»’è
	bool IsCollision(const OBB& obb1, const OBB& obb2);
}
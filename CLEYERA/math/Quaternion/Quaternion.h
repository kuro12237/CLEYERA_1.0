#pragma once

#include"VectorTransform.h"
#include"MatrixTransform.h"

class Quaternion
{
public:
	
	static Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);
	
	static Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);

private:

};


#pragma once

#include"VectorTransform.h"
#include"MatrixTransform.h"

class Quaternion
{
public:
	
	static Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);

private:

};


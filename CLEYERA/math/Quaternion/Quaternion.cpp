#include "Quaternion.h"

Matrix4x4 Quaternion::MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Matrix4x4 result{};
	float cosAngle = cosf(angle);
	float sinAngle = sinf(angle);

	result = MatrixTransform::Identity();

	result.m[0][0] = (axis.x * axis.x) * (1 - cosAngle) + cosAngle;
	result.m[0][1] = (axis.x * axis.y) * (1 - cosAngle) - axis.z * sinAngle;
	result.m[0][2] = (axis.x * axis.z) * (1 - cosAngle) + axis.y * sinAngle;
											  
	result.m[1][0] = (axis.x * axis.y) * (1 - cosAngle) + axis.z * sinAngle;
	result.m[1][1] = (axis.y * axis.y) * (1 - cosAngle) + cosAngle;
	result.m[1][2] = (axis.y * axis.z) * (1 - cosAngle) - axis.x * sinAngle;
											  
	result.m[2][0] = (axis.x * axis.z) * (1 - cosAngle) - axis.y * sinAngle;
	result.m[2][1] = (axis.y * axis.z) * (1 - cosAngle) + axis.x * sinAngle;
	result.m[2][2] = (axis.z * axis.z) * (1 - cosAngle) + cosAngle;
	return result;
}

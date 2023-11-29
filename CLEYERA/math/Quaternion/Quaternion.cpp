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

Matrix4x4 Quaternion::DirectionToDirection(const Vector3& from,const Vector3& to)
{
	Vector3 fromVec = VectorTransform::Normalize(from);
	Vector3 toVec = VectorTransform::Normalize(to);

	 Vector3 uvCross = VectorTransform::Cross(fromVec, toVec);
	 Vector3 n = VectorTransform::Normalize(uvCross);
	 
	 float cos = VectorTransform::Dot(fromVec, toVec);
	 float sin = VectorTransform::Length(VectorTransform::Cross(fromVec, toVec));

	 Matrix4x4 resultR = MatrixTransform::Identity();
	 resultR.m[0][0] = n.x * n.x * (1 - cos) + cos;
	 resultR.m[0][1] = n.x * n.y * (1 - cos) - n.z * sin;
	 resultR.m[0][2] = n.x * n.z * (1 - cos) + n.y * sin;

	 resultR.m[1][0] = n.y * n.x * (1 - cos) + n.z * sin;
	 resultR.m[1][1] = n.y * n.y * (1 - cos) + cos;
	 resultR.m[1][2] = n.y * n.z * (1 - cos) - n.x * sin;
	
	 resultR.m[2][0] = n.z * n.x * (1 - cos) - n.y * sin;
	 resultR.m[2][1] = n.z * n.y * (1 - cos) + n.x * sin;
	 resultR.m[2][2] = n.z * n.z * (1 - cos) + cos;
	
	return resultR;
}

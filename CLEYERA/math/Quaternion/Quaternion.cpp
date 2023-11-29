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

Matrix4x4 Quaternion::MakeRotateAxisAngle(const Vector3& axis, float sin, float cos)
{
	Matrix4x4 result = MatrixTransform::Identity();
	result.m[0][0] = axis.x * axis.x * (1 - cos) + cos;
	result.m[0][1] = axis.x * axis.y * (1 - cos) - axis.z * sin;
	result.m[0][2] = axis.x * axis.z * (1 - cos) + axis.y * sin;
					  		   
	result.m[1][0] = axis.x * axis.y * (1 - cos) + axis.z * sin;
	result.m[1][1] = axis.y * axis.y * (1 - cos) + cos;
	result.m[1][2] = axis.y * axis.z * (1 - cos) - axis.x * sin;
					  		   
	result.m[2][0] = axis.x * axis.z * (1 - cos) - axis.y * sin;
	result.m[2][1] = axis.y * axis.z * (1 - cos) + axis.x * sin;
	result.m[2][2] = axis.z * axis.z * (1 - cos) + cos;
	return result;
}

Matrix4x4 Quaternion::DirectionToDirection(const Vector3& from,const Vector3& to)
{
	Vector3 fromVec = VectorTransform::Normalize(from);
	Vector3 toVec = VectorTransform::Normalize(to);
	 Vector3 n = VectorTransform::Normalize(VectorTransform::Cross(fromVec, toVec));
	 
	 float cos = VectorTransform::Dot(fromVec, toVec);
	 float sin = VectorTransform::Length(VectorTransform::Cross(fromVec, toVec));

	 if (from.x == -to.x && from.y == -to.y && from.z == -to.z) 
	 {
		 if (from.x != 0.0f || from.y != 0.0f) 
		 {
			 n = { from.y,-from.x,0.0f };
		 }
		 else if (from.x != 0.0f || from.z != 0.0f) 
		 {
			 n = { from.z,0.0f,-from.x };
		 }
	 }

	 Matrix4x4 result{};

	 result = MakeRotateAxisAngle(n, sin, cos);

	return result;
}

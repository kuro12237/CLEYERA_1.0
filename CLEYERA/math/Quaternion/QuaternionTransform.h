#pragma once

#include"VectorTransform.h"
#include"MatrixTransform.h"
#include"Quaternion.h"


class QuaternionTransform
{
public:
	
	static Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);
	
	static Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float sin, float cos);

	static Quaternion MakeQuaternionRotateAxisAngle(const Vector3& axis, float angle);

	static Matrix4x4 MakeRotateMatrix(const Quaternion& q);

	static Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);

	static float Length(Quaternion q);

	static float Dot(const Quaternion& q1, const Quaternion& q2);

	static Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);

	static Quaternion IdentityQuaternion();

	static Quaternion Conjugation(const Quaternion& quaternion);

	static float Norm(const Quaternion& quaternion);

	static Quaternion Normalize(const Quaternion& quaternion);

	static Quaternion Inverse(const Quaternion& quaternion);

	static Vector3 RotateVector(const Vector3& v, const Quaternion& q);

	static Quaternion Slerp(const Quaternion& q1,const Quaternion& q2, float t);

private:

};


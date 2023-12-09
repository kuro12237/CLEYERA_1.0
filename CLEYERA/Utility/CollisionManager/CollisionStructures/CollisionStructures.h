#pragma once
#include "Vector3.h"

// ��
struct Sphere {
	Vector3 center;
	float radius;
};


// ����
struct Line {
	Vector3 origin;	// !< �n�_
	Vector3 diff;   // !< �I�_�ւ̍����x�N�g��
};


// ������
struct Ray {
	Vector3 origin;	// !< �n�_
	Vector3 diff;   // !< �I�_�ւ̍����x�N�g��
};


// ����
struct Segment {
	Vector3 origin;	// !< �n�_
	Vector3 diff;   // !< �I�_�ւ̍����x�N�g��
};


// ����
struct Plane {
	Vector3 normal;	// !< �@��
	float distance; // !< ����
};


// �O�p�`
struct Triangle {
	Vector3 vertices[3]; // !< ���_
};


// AABB
struct AABB {
	Vector3 min; // !< �ŏ��_
	Vector3 max; // !< �ő�_
};


// OBB
struct OBB {
	Vector3 center;			   // !< ���S�_
	Vector3 orientations[3]{}; // !< ���W���B���K���E����K�{
	Vector3 halfSize;          // !< ���W�������̒����̔����B���S����ʂ܂ł̋���
};
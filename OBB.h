#pragma once

#include "Vector3.h"
#include "Matrix3D.h"

typedef struct OrientedBoundingBox {

	// 中心
	Vector3 center{};

	// x, y, z
	Vector3 axis[3];
	
	// 大きさ
	Vector3 size;

} OBB;

void RotateObbAxis(OBB& obb, const Vector3& rotate);

void SetObbAxis(OBB& obb, const Matrix4x4& rotateMatrix);

void SetObbAxis(OBB& obb, const Vector3& rotate);

Matrix4x4 GetObbWorldMatrix(const OBB& obb);
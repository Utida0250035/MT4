#include "OBB.h"
#include "Matrix3D.h"

void RotateObbAxis(OBB& obb, const Vector3& rotateVelovity) {

	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotateVelovity);

	obb.axis[0] = VectorTransform(obb.axis[0], rotateMatrix);

	obb.axis[1] = VectorTransform(obb.axis[1], rotateMatrix);

	obb.axis[2] = VectorTransform(obb.axis[2], rotateMatrix);

}

void SetObbAxis(OBB& obb, const Matrix4x4& rotateMatrix) {

	obb.axis[0] = { rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2] };

	obb.axis[1] = { rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2] };

	obb.axis[2] = { rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2] };

}

void SetObbAxis(OBB& obb, const Vector3& rotate) {

	SetObbAxis(obb, MakeRotateMatrix(rotate));

}

Matrix4x4 GetObbWorldMatrix(const OBB& obb) {

	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = obb.axis[0].x;
	result.m[0][1] = obb.axis[0].y;
	result.m[0][2] = obb.axis[0].z;

	result.m[1][0] = obb.axis[1].x;
	result.m[1][1] = obb.axis[1].y;
	result.m[1][2] = obb.axis[1].z;

	result.m[2][0] = obb.axis[2].x;
	result.m[2][1] = obb.axis[2].y;
	result.m[2][2] = obb.axis[2].z;

	result.m[3][0] = obb.center.x;
	result.m[3][1] = obb.center.y;
	result.m[3][2] = obb.center.z;

	return result;

}
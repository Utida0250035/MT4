#pragma once

#include "Vector3.h"
#include "Matrix3D.h"

struct Transform{
	Vector3 scale{1.0f, 1.0f, 1.0f};
	Vector3 rotate{};
	Vector3 translate{};
};

inline Matrix4x4 MakeWorldMatrix(const Transform& transform) {

	return MakeScaleMatrix(transform.scale) * MakeRotateMatrix(transform.rotate) * MakeTranslateMatrix(transform.translate);

}
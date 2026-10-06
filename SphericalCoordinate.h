#pragma once

#include "Vector3.h"

struct Matrix4x4;

typedef struct SphericalCoordinate {

	float radius;
	float theta;
	float phi;

	Vector3 ToCartesian() const;

	Matrix4x4 CameraMatrix(const Vector3& target = { 0.0f, 0.0f, 0.0f }) const;

	void Imgui();

} Spherical;
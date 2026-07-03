#pragma once

#include "Vector3.h"
#include <cassert>

struct ConicalPendulum {
	Vector3 anchorPos;
	Vector3 bobPos;
	float length;
	float halfApexAngle;
	float angle;
	float angularVelocity;
};

inline constexpr Vector3 VelocityFromOmega2D(const ConicalPendulum& conicalPendulum) {

	Vector3 difference = conicalPendulum.anchorPos - conicalPendulum.bobPos;

	return Vector3{
		-conicalPendulum.angularVelocity * difference.z,
		0.0f,
		conicalPendulum.angularVelocity * difference.x,
	};

}

inline constexpr Vector3 AccelerationFromOmega2D(const ConicalPendulum& conicalPendulum) {

	Vector3 anchorToWeight = conicalPendulum.anchorPos - conicalPendulum.bobPos;

	float omegaSquare = conicalPendulum.angularVelocity * conicalPendulum.angularVelocity;

	return Vector3{
		-omegaSquare * anchorToWeight.x,
		0.0f,
		-omegaSquare * anchorToWeight.z
	};

}
#pragma once

#include "Vector3.h"
#include <cassert>

struct Pendulum {

	Vector3 anchorPos;
	Vector3 weightPos;
	float length;
	float angle;
	float angularVelocity;
	float angularAcceleration;

};

inline constexpr Vector3 VelocityFromOmega2D(const Pendulum& pendulum) {

	Vector3 difference = pendulum.anchorPos - pendulum.weightPos;

	assert(difference.z == 0.0f);

	return Vector3{
		pendulum.angularVelocity * difference.y,
		-pendulum.angularVelocity * difference.x,
		0.0f
	};

}

inline constexpr Vector3 AccelerationFromOmegaAndAlpha2D(const Pendulum& pendulum) {

	Vector3 anchorToWeight = pendulum.anchorPos - pendulum.weightPos;

	assert(anchorToWeight.z == 0.0f);

	float omegaSquare = pendulum.angularVelocity * pendulum.angularVelocity;

	return Vector3{
		pendulum.angularAcceleration * anchorToWeight.y - omegaSquare * anchorToWeight.x,
		-pendulum.angularAcceleration * anchorToWeight.x - omegaSquare * anchorToWeight.y,
		0.0f
	};

}
#include "Movement.h"
#include <cmath>

void SpringBallMovement(Spring& spring, Ball& ball, const Vector3 gravity, const float deltaTime) {

	Vector3 diff = ball.position - spring.anchor;
	float length = VectorLength(diff);

	if (length != 0.0f) {

		Vector3 direction = VectorNormalize(diff);
		Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
		Vector3 displacement = length * (ball.position - restPosition);
		Vector3 restoringForce = -spring.stiffness * displacement;
		Vector3 dampingForce = -spring.dampingCoefficient * ball.velocity;
		Vector3 force = restoringForce + dampingForce;
		ball.acceleration = force / ball.mass;

	}

	ball.acceleration += gravity;

	ball.velocity += ball.acceleration * deltaTime;
	ball.position += ball.velocity * deltaTime;

}

void PendulumBallMovement2D(Pendulum& pendulum, Ball& ball, const float gravity, const float deltaTime) {

	pendulum.angularAcceleration = gravity / pendulum.length * std::sin(pendulum.angle);

	pendulum.angularVelocity += pendulum.angularAcceleration * deltaTime;

	pendulum.angle += pendulum.angularVelocity * deltaTime;

	pendulum.weightPos = {
		pendulum.anchorPos.x + std::sin(pendulum.angle) * pendulum.length,
		pendulum.anchorPos.y - std::cos(pendulum.angle) * pendulum.length,
		pendulum.anchorPos.z
	};

	ball.position = pendulum.weightPos;

	ball.velocity = VelocityFromOmega2D(pendulum);

	ball.acceleration = AccelerationFromOmegaAndAlpha2D(pendulum);

}
#include "Movement.h"
#include <cmath>
#include <numbers>

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

	pendulum.bobPos = {
		pendulum.anchorPos.x + std::sin(pendulum.angle) * pendulum.length,
		pendulum.anchorPos.y - std::cos(pendulum.angle) * pendulum.length,
		pendulum.anchorPos.z
	};

	ball.position = pendulum.bobPos;

	ball.velocity = VelocityFromOmega2D(pendulum);

	ball.acceleration = AccelerationFromOmegaAndAlpha2D(pendulum);

}

void ConicalPendulumBallMovement2D(ConicalPendulum& conicalPendulum, Ball& bob, const float gravity, const float deltaTime) {

	conicalPendulum.angularVelocity = std::sqrt(-gravity / (conicalPendulum.length * std::cos(conicalPendulum.halfApexAngle)));
	conicalPendulum.angle += conicalPendulum.angularVelocity * deltaTime;

	if (conicalPendulum.angle <= 0.0f || conicalPendulum.angle >= std::numbers::pi_v<float> * 2.0f) {

		conicalPendulum.angle = std::fmod(conicalPendulum.angle, std::numbers::pi_v<float> * 2.0f);

	}

	float radius = std::sin(conicalPendulum.halfApexAngle) * conicalPendulum.length;
	float height = std::cos(conicalPendulum.halfApexAngle) * conicalPendulum.length;

	conicalPendulum.bobPos = {
		conicalPendulum.anchorPos.x + std::cos(conicalPendulum.angle) * radius,
		conicalPendulum.anchorPos.y - height,
		conicalPendulum.anchorPos.z - std::sin(conicalPendulum.angle) * radius
	};

	bob.position = conicalPendulum.bobPos;

	bob.acceleration = AccelerationFromOmega2D(conicalPendulum);
	bob.velocity = VelocityFromOmega2D(conicalPendulum);

}
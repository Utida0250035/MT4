#include "Movement.h"

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
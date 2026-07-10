#include "Movement.h"
#include "Reflect.h"
#include "Collision.h"
#include <cmath>
#include <numbers>

void SpringBallMovement(Spring& spring, Ball& ball, const Vector3 gravity, const float deltaTime) {

	Vector3 diff = ball.position - spring.anchor;
	float length = VectorLength(diff);

	if (length != 0.0f) {

		Vector3 direction = VectorNormalize(diff);
		Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
		Vector3 displacement = ball.position - restPosition;
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

	if (conicalPendulum.angle <= 0.0f || conicalPendulum.angle >= std::numbers::pi_v<float> *2.0f) {

		conicalPendulum.angle = std::fmod(conicalPendulum.angle, std::numbers::pi_v<float> *2.0f);

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

static bool GetHitTimeLinePlane(const Segment& segment, const Plane& plane, float& t) {
	// 平面の法線と移動方向のドット積を計算
	float denominator = VectorDot(segment.difference, plane.normal);

	// 平面と線分が平行な場合（またはほぼ平行）
	if (std::abs(denominator) < 1e-6f) {
		return false;
	}

	// 衝突点の計算
	// 平面の原点から線分の始点へのベクトル
	Vector3 startToPlane = plane.distance * plane.normal - segment.origin;

	// 平面までの符号付き距離を計算
	t = VectorDot(startToPlane, plane.normal) / denominator;

	// 線分の範囲内(0.0 <= t <= 1.0)かを確認
	if (t >= 0.0f && t <= 1.0f) {
		return true;
	}

	return false;
}

void BallReflectPlane(Ball& ball, const Plane& plane, const float e, const float deltaTime) {

	const bool isHit = IsCapsuleHitPlane(Capsule{ Segment{ball.position - ball.velocity * deltaTime, ball.velocity * deltaTime}, ball.radius }, plane);

	if (isHit) {
		float t = 0.0f;

		Segment segment{ ball.position - ball.velocity * deltaTime, ball.velocity };

		if (GetHitTimeLinePlane(segment, plane, t)) {
			ball.position = (ball.position - ball.velocity * deltaTime) + ball.velocity * t + (plane.normal * ball.radius);
			ball.position += plane.normal * 0.01f;
		}

		float dot = VectorDot(ball.velocity, plane.normal);
		Vector3 vNormal = plane.normal * dot;
		Vector3 vTangent = ball.velocity - vNormal;

		ball.velocity = vTangent - (vNormal * e);
	}
}
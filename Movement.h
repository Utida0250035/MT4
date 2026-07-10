#pragma once
#include "Ball.h"
#include "ConicalPendulum.h"
#include "Pendulum.h"
#include "Plane.h"
#include "Sphere.h"
#include "Spring.h"
#include "Vector3.h"

void SpringBallMovement(Spring& spring, Ball& ball, const Vector3 gravity,  const float deltaTime);

void PendulumBallMovement2D(Pendulum& pendulum, Ball& ball, const float gravity, const float deltaTime);

void ConicalPendulumBallMovement2D(ConicalPendulum& pendulum, Ball& bob, const float gravity, const float deltaTime);

void BallReflectPlane(Ball& ball, const Plane& plane, const float e, const float deltaTime);
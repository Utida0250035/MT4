#pragma once
#include "Spring.h"
#include "Ball.h"
#include "Sphere.h"
#include "Pendulum.h"

void SpringBallMovement(Spring& spring, Ball& ball, const Vector3 gravity,  const float deltaTime);

void PendulumBallMovement2D(Pendulum& pendulum, Ball& ball, const float gravity, const float deltaTime);
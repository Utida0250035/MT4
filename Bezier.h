#pragma once

#include "Vector3.h"
#include "Vector2.h"

struct Bezier2Vec3 {
	Vector3 p[3]{};
};

struct Bezier2Vec2 {
	Vector2 p[3]{};
};

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const float t);
Vector2 BezierDeriative(const Vector2& p0, const Vector2& p1, const Vector2& p2, const float t);

Vector2 Bezier(const Bezier2Vec2& bezier, const float t);

Vector2 BezierDeriative(const Bezier2Vec2& bezier, const float t);
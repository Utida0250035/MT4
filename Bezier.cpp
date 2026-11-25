#include "Bezier.h"

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, const float t) {

	return (1 - t) * (1 - t) * p0 + 2.0f * t * (1.0f - t) * p1 + t * t * p2;

}

Vector2 BezierDeriative(const Vector2& p0, const Vector2& p1, const Vector2& p2, const float t) {

	return 2.0f * (1.0f - t) * (p1 - p0) + 2.0f * t * (p2 - p1);

}

Vector2 Bezier(const Bezier2Vec2& bezier, const float t) {

	return Bezier(bezier.p[0], bezier.p[1], bezier.p[2], t);

}

Vector2 BezierDeriative(const Bezier2Vec2& bezier, const float t) {

	return BezierDeriative(bezier.p[0], bezier.p[1], bezier.p[2], t);

}
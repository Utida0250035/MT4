#pragma once

struct Vector2 {
	float x;
	float y;
};

float VectorLength(const Vector2& me);

inline float VectorLengthSquare(const Vector2& me) {

	return me.x * me.x + me.y * me.y;

}

inline Vector2 VectorNorm(const Vector2& me) {

	float length = VectorLength(me);

	if (length < 0.00001f) {

		return { 0.0, 0.0f };

	} else {

		return { me.x / length, me.y / length };

	}

}

inline float VectorDot(const Vector2& me, const Vector2& other) {

	return me.x * other.x + me.y * other.y;

}

inline float VectorCross(const Vector2& me, const Vector2& other) {

	return me.x * other.y - me.y * other.x;

}

inline Vector2 operator+(const Vector2& me ,const Vector2& other) {

	return { me.x + other.x, me.y + other.y };

}

inline void operator+=(Vector2& me, const Vector2& other) {

	me.x += other.x;
	me.y += other.y;

}

inline Vector2 operator-(const Vector2& me, const Vector2& other) {

	return { me.x - other.x, me.y - other.y };

}

inline Vector2 operator-(const Vector2& me) {

	return { -me.x, -me.y};

}

inline void operator-=(Vector2& me, const Vector2& other) {

	me.x -= other.x;
	me.y -= other.y;

}

inline Vector2 operator*(const Vector2& me, const float& scalar) {

	return { me.x * scalar, me.y * scalar };

}

inline Vector2 operator*(const float& scalar, const Vector2& vector) {

	return { scalar * vector.x, scalar * vector.y };

}

inline void operator*=(Vector2& me, const float& scalar) {

	me.x *= scalar;
	me.y *= scalar;

}

inline Vector2 operator/(const Vector2& me, const float& scalar) {

	return { me.x / scalar, me.y / scalar };

}

inline void operator/=(Vector2& me, const float& scalar) {

	me.x /= scalar;
	me.y /= scalar;

}
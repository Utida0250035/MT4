#include "Vector3.h"
#include <cmath>
#include <Novice.h>
#include <algorithm>

float VectorLength(const Vector3& vector) {

	return std::sqrtf(VectorLengthSquare(vector));

}

Vector3 VectorProjectClamped(const Vector3& me, const Vector3& other) {

	float t = VectorDot(me, other) / VectorLengthSquare(other);

	t = std::clamp(t, 0.0f, 1.0f);

	return t * other;

}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kVectorPrintColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kVectorPrintColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kVectorPrintColumnWidth * 3, y, "%s", label);

}

Vector3 PerpendicularAny(const Vector3& vector) {

	if (std::abs(vector.x) >= 0.00001f || std::abs(vector.y) >= 0.00001f) {

		return { -vector.y, vector.x, 0.0f };

	}

	return { 0.0f, -vector.x, vector.y };

}

Vector3 Lerp(const Vector3& from, const Vector3& to, const float t) {

	return { std::lerp(from.x, to.x, t), std::lerp(from.y, to.y, t), std::lerp(from.z, to.z, t) };

}
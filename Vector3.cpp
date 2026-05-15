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
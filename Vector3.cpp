#include "Vector3.h"
#include <cmath>
#include <Novice.h>

float VectorLength(const Vector3& vector) {

	return std::sqrtf(VectorLengthSquare(vector));

}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {

	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kVectorPrintColumnWidth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kVectorPrintColumnWidth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kVectorPrintColumnWidth * 3, y, "%s", label);

}
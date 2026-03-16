#include "NoviceUtility.h"
#include <Novice.h>

void NoviceUtility::DrawLine(const Vector3& lineStartPos, const Vector3& lineEndPos, const uint32_t color) {

	Novice::DrawLine(
		static_cast<int>(lineStartPos.x), static_cast<int>(lineStartPos.y),
		static_cast<int>(lineEndPos.x), static_cast<int>(lineEndPos.y),
		color
	);

}

void NoviceUtility::DrawCircle(const Vector3& centerPos, const float& radius, const uint32_t color) {

	Novice::DrawEllipse(
		static_cast<int>(centerPos.x), static_cast<int>(centerPos.y),
		static_cast<int>(radius), static_cast<int>(radius),
		0.0f,
		color,
		kFillModeSolid
	);

}
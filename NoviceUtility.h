#pragma once

#include "Vector3.h"
#include <stdint.h>

class NoviceUtility {

public:

	static void DrawLine(const Vector3& lineStartPos, const Vector3& lineEndPos, const uint32_t color);

	static void DrawCircle(const Vector3& centerPos, const float& radius, const uint32_t color);

};
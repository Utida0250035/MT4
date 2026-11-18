#pragma once

#include "Vector3.h"
#include "Vector2.h"
#include <stdint.h>

class NoviceUtility {

public:

	static void DrawLine(const Vector3& lineStartPos, const Vector3& lineEndPos, const uint32_t color);

	static void DrawLine(const Vector2& lineStartPos, const Vector2& lineEndPos, const uint32_t color);

	static void DrawCircle(const Vector3& centerPos, const float& radius, const uint32_t color);

	static void DrawCircle(const Vector2& centerPos, const float& radius, const uint32_t color);

};
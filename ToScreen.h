#pragma once

#include "Vector2.h"

inline constexpr Vector2 ToScreen(const Vector2& posWorld) {

	return { posWorld.x + 256.0f, -posWorld.y + 592.0f };

}
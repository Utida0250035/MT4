#pragma once

#include <numbers>

inline constexpr float RadianToDegree(const float radian) {

	return radian / 180.0f * std::numbers::pi_v<float>;

}

inline constexpr float DegreeToRadian(const float degree) {

	return degree * 180.0f / std::numbers::pi_v<float>;

}
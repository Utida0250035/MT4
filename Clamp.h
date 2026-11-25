#pragma once

#include <algorithm>

template<typename T>
void Clamp(T& val, const T& min, const T& max) {

	val = std::clamp(val, min, max);

}
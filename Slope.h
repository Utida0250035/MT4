#pragma once

#include <limits>
#include <numbers>

namespace ConstSlope {

	inline constexpr float f(float x) {

		return 0.125f * x * x * x + 0.25f * x * x;

	}

	inline constexpr float fPrimeByDerivative(float x) {

		constexpr float h = 1e-5f;

		return (f(x + h) - f(x)) / h;

	}

	inline constexpr float fPrime(float x) {
		
		return 0.375f * x * x + 0.5f * x;

	}

}
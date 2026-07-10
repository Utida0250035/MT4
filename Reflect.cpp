#include "Reflect.h"
#include "Vector3.h"

Vector3 Reflect(const Vector3& input, const Vector3& normal) {

	return input - 2.0f * (VectorDot(input, normal)) * normal;

}
#include "Collision.h"

bool IsHitSpheres(const Sphere& sphere1, const Sphere& sphere2) {

	Vector3 diff = sphere1.center - sphere2.center;

	float distance = VectorLength(diff);

	if (distance < sphere1.radius + sphere2.radius) {

		return true;

	}

	return false;

}
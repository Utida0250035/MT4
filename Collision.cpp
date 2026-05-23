#include "Collision.h"
#include <cmath> 

bool IsHitSpheres(const Sphere& sphere1, const Sphere& sphere2) {

	Vector3 diff = sphere1.center - sphere2.center;

	float distance = VectorLength(diff);

	if (distance < sphere1.radius + sphere2.radius) {

		return true;

	}

	return false;

}

bool IsSphereHitPlane(const Sphere& sphere, const Plane& plane){

	float distance = std::abs(CalcDistance(plane, sphere.center));

	if (distance < sphere.radius) {

		return true;

	}

	return false;

}

bool CalcT(const Vector3& origin, const Vector3& difference, const Plane& plane, float& t) {

	float dot = VectorDot(difference, plane.normal);

	if (std::abs(dot) <= 0.00001f) {

		return false;

	}

	t = (plane.distance - VectorDot(origin, plane.normal)) / dot;

	return true;

}

bool IsLineHitPlane(const Line& line, const Plane& plane) {

	float t = 0.0f;

	if (!CalcT(line.origin, line.difference, plane, t)) {

		return false;

	}

	return true;

}

bool IsSegmentHitPlane(const Segment& segment, const Plane& plane) {

	float t = 0.0f;

	if (!CalcT(segment.origin, segment.difference, plane, t)) {

		return false;

	}

	if (t <= 1.0f && t >= 0.0f) {

		return true;

	}

	return false;

}

bool IsRayHitPlane(const Ray& ray, const Plane& plane) {

	float t = 0.0f;

	if (!CalcT(ray.origin, ray.difference, plane, t)) {

		return false;

	}

	if (t >= 0.0f) {

		return true;

	}

	return false;

}
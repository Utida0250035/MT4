#include "Collision.h"
#include <cmath>
#include <algorithm>
#include <limits>

bool IsHitSpheres(const Sphere& sphere1, const Sphere& sphere2) {

	Vector3 diff = sphere1.center - sphere2.center;

	float distance = VectorLength(diff);

	if (distance < sphere1.radius + sphere2.radius) {

		return true;

	}

	return false;

}

bool IsSphereHitPlane(const Sphere& sphere, const Plane& plane) {

	float distance = std::abs(CalcDistance(plane, sphere.center));

	if (distance < sphere.radius) {

		return true;

	}

	return false;

}

static bool CalcT(const Vector3& origin, const Vector3& difference, const Plane& plane, float& t) {

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

static bool IsLineHitPlane(const Line& line, const Plane& plane, float& t) {

	if (!CalcT(line.origin, line.difference, plane, t)) {

		return false;

	}

	return true;

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

static bool IsRayHitPlane(const Ray& ray, const Plane& plane, float& t) {

	if (!CalcT(ray.origin, ray.difference, plane, t)) {

		return false;

	}

	if (t >= 0.0f) {

		return true;

	}

	return false;

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

static bool IsSegmentHitPlane(const Segment& segment, const Plane& plane, float& t) {

	if (!CalcT(segment.origin, segment.difference, plane, t)) {

		return false;

	}

	if (t <= 1.0f && t >= 0.0f) {

		return true;

	}

	return false;

}

static bool IsPointInTriangle(const Vector3& point, const Triangle& triangle, const Vector3& normal) {

	const auto& vertices = triangle.vertices;

	// 三角形の頂点を右回りに結んだベクトル
	Vector3 v0To1 = vertices[1] - vertices[0];
	Vector3 v1To2 = vertices[2] - vertices[1];
	Vector3 v2To0 = vertices[0] - vertices[2];

	// 三角形の各頂点から点Pへのベクトル
	Vector3 v0ToP = point - vertices[0];
	Vector3 v1ToP = point - vertices[1];
	Vector3 v2ToP = point - vertices[2];

	// 右回りのベクトルと点Pへのベクトルのクロス積
	// (各辺と点Pで構成される小三角形の向きをもつベクトル)
	Vector3 cross1 = VectorCross(v0To1, v1ToP);
	Vector3 cross2 = VectorCross(v1To2, v2ToP);
	Vector3 cross3 = VectorCross(v2To0, v0ToP);

	if (VectorDot(cross1, normal) >= 0.0f) {
		if (VectorDot(cross2, normal) >= 0.0f) {
			if (VectorDot(cross3, normal) >= 0.0f) {
				// 小三角形が全て元の三角形と同じ向きを向いていれば衝突

				return true;

			}

		}

	}

	return false;

}

bool IsLineHitTriangle(const Line& line, const Triangle& triangle) {

	Plane plane = MakePlane(triangle.vertices);

	float t = 0.0f;

	if (!IsLineHitPlane(line, plane, t)) {

		return false;

	}

	Vector3 contact = line.origin + t * line.difference;

	return IsPointInTriangle(contact, triangle, plane.normal);

}

bool IsRayHitTriangle(const Ray& ray, const Triangle& triangle) {

	Plane plane = MakePlane(triangle.vertices);

	float t = 0.0f;

	if (!IsRayHitPlane(ray, plane, t)) {

		return false;

	}

	Vector3 contact = ray.origin + t * ray.difference;

	return IsPointInTriangle(contact, triangle, plane.normal);

}

bool IsSegmentHitTriangle(const Segment& segment, const Triangle& triangle) {

	Plane plane = MakePlane(triangle.vertices);

	float t = 0.0f;

	if (!IsSegmentHitPlane(segment, plane, t)) {

		return false;

	}

	Vector3 contact = segment.origin + t * segment.difference;

	return IsPointInTriangle(contact, triangle, plane.normal);

}

bool IsHitAABBs(const AABB& box1, const AABB& box2) {

	if (box1.min.x <= box2.max.x && box1.max.x >= box2.min.x) {

		if (box1.min.y <= box2.max.y && box1.max.y >= box2.min.y) {

			if (box1.min.z <= box2.max.z && box1.max.z >= box2.min.z) {

				return true;

			}

		}

	}

	return false;

}

bool IsSphereHitAABB(const Sphere& sphere, const AABB& aabb) {

	Vector3 closestPoint{
		std::clamp(sphere.center.x, aabb.min.x, aabb.max.x),
		std::clamp(sphere.center.y, aabb.min.y, aabb.max.y),
		std::clamp(sphere.center.z, aabb.min.z, aabb.max.z),
	};

	if (VectorLength(closestPoint - sphere.center) <= sphere.radius) {

		return true;

	}

	return false;

}

bool IsPointHitAABB(const Vector3& point, const AABB& aabb) {

	if (point.x <= aabb.max.x && point.x >= aabb.min.x) {

		if (point.y <= aabb.max.y && point.y >= aabb.min.y) {

			if (point.z <= aabb.max.z && point.z >= aabb.min.z) {

				return true;

			}

		}

	}

	return false;

}

static bool IsGenericLineIntersectAABB(const Vector3& origin, const Vector3& difference, const AABB& aabb, float& tNear, float& tFar) {

	tNear = -std::numeric_limits<float>::infinity();
	tFar = std::numeric_limits<float>::infinity();

	float originByArray[3] = { origin.x, origin.y, origin.z };
	float differenceByArray[3] = { difference.x, difference.y, difference.z };
	float boxMinByArray[3] = { aabb.min.x, aabb.min.y, aabb.min.z };
	float boxMaxByArray[3] = { aabb.max.x, aabb.max.x, aabb.max.z };

	float t1 = 0.0f;
	float t2 = 0.0f;

	for (size_t i = 0; i < 3; i++) {

		if (std::abs(differenceByArray[i]) < 1e-5f) {

			if (originByArray[i] < boxMinByArray[i] || originByArray[i] > boxMaxByArray[i]) {
				// 線が軸に平行かつ始点がAABBの外側にある場合 衝突なし

				return false;

			}

		} else {

			t1 = (boxMinByArray[i] - originByArray[i]) / differenceByArray[i];
			t2 = (boxMaxByArray[i] - originByArray[i]) / differenceByArray[i];

			if (t1 > t2) {

				std::swap(t1, t2);

			}

			tNear = std::max(tNear, t1);
			tFar = std::min(tFar, t2);

			if (tNear > tFar) {
				// 区間崩壊 衝突なし

				return false;

			}

		}

	}

	return true;

}

bool IsLineHitAABB(const Line& segment, const AABB& aabb) {

	float tNear = 0.0f;
	float tFar = 0.0f;

	if (!IsGenericLineIntersectAABB(segment.origin, segment.difference, aabb, tNear, tFar)) {

		return false;

	}

	return true;

}

bool IsRayHitAABB(const Ray& segment, const AABB& aabb) {

	float tNear = 0.0f;
	float tFar = 0.0f;

	if (!IsGenericLineIntersectAABB(segment.origin, segment.difference, aabb, tNear, tFar)) {

		return false;

	}

	if (tFar < 0.0f) {

		return false;

	}

	return true;

}

bool IsSegmentHitAABB(const Segment& segment, const AABB& aabb) {

	float tNear = 0.0f;
	float tFar = 0.0f;

	if (!IsGenericLineIntersectAABB(segment.origin, segment.difference, aabb, tNear, tFar)) {

		return false;

	}

	if (tFar < 0.0f || tNear > 1.0f) {

		return false;

	}

	return true;

}


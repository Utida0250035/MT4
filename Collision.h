#pragma once

#include "AABB.h"
#include "Capsule.h"
#include "Line.h"
#include "OBB.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"

bool IsHitSpheres(const Sphere& sphere1, const Sphere& sphere2);

bool IsSphereHitPlane(const Sphere& sphere, const Plane& plane);

bool IsLineHitPlane(const Line& line, const Plane& plane);
bool IsLineHitPlane(const Line& line, const Plane& plane, float& t);

bool IsRayHitPlane(const Ray& ray, const Plane& plane);
bool IsRayHitPlane(const Ray& ray, const Plane& plane, float& t);

bool IsSegmentHitPlane(const Segment& segment, const Plane& plane);
bool IsSegmentHitPlane(const Segment& segment, const Plane& plane, float& t);


bool IsLineHitTriangle(const Line& line, const Triangle& triangle);
bool IsLineHitTriangle(const Line& line, const Triangle& triangle, float& t);


bool IsRayHitTriangle(const Ray& ray, const Triangle& triangle);
bool IsRayHitTriangle(const Ray& ray, const Triangle& triangle, float& t);

bool IsSegmentHitTriangle(const Segment& segment, const Triangle& triangle);
bool IsSegmentHitTriangle(const Segment& segment, const Triangle& triangle, float& t);

bool IsHitAABBs(const AABB& box1, const AABB& box2);

bool IsSphereHitAABB(const Sphere& sphere, const AABB& aabb);
bool IsSphereHitAABB(const Sphere& sphere, const AABB& aabb, Vector3& closestPoint);

bool IsPointHitAABB(const Vector3& point, const AABB& aabb);

bool IsLineHitAABB(const Line& segment, const AABB& aabb);
bool IsLineHitAABB(const Line& segment, const AABB& aabb, float& tNear, float& tFar);

bool IsRayHitAABB(const Ray& segment, const AABB& aabb);
bool IsRayHitAABB(const Ray& segment, const AABB& aabb, float& tNear, float& tFar);

bool IsSegmentHitAABB(const Segment& segment, const AABB& aabb);
bool IsSegmentHitAABB(const Segment& segment, const AABB& aabb, float& tNear, float& tFar);

bool IsSphereHitOBB(const Sphere& sphere, const OBB& obb);

bool IsLineHitOBB(const Line& line, const OBB& obb);
bool IsLineHitOBB(const Line& line, const OBB& obb, float& tNear, float& tFar);

bool IsRayHitOBB(const Ray& ray, const OBB& obb);
bool IsRayHitOBB(const Ray& ray, const OBB& obb, float& tNear, float& tfar);

bool IsSegmentHitOBB(const Segment& segment, const OBB& obb);
bool IsSegmentHitOBB(const Segment& segment, const OBB& obb, float& tNear, float& tFar);

bool IsObbHitObb(const OBB& obb1, const OBB& obb2);

bool IsCapsuleHitPlane(const Capsule& capsule, const Plane& plane);

bool IsCapsuleHitPlane(const Capsule& capsule, const Plane& plane, float& t);
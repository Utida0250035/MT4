#pragma once

#include "AABB.h"
#include "Line.h"
#include "OBB.h"
#include "Plane.h"
#include "Sphere.h"
#include "Triangle.h"

bool IsHitSpheres(const Sphere& sphere1, const Sphere& sphere2);


bool IsSphereHitPlane(const Sphere& sphere, const Plane& plane);


bool IsLineHitPlane(const Line& line, const Plane& plane);

bool IsRayHitPlane(const Ray& ray, const Plane& plane);

bool IsSegmentHitPlane(const Segment& segment, const Plane& plane);


bool IsLineHitTriangle(const Line& line, const Triangle& triangle);

bool IsRayHitTriangle(const Ray& ray, const Triangle& triangle);

bool IsSegmentHitTriangle(const Segment& segment, const Triangle& triangle);

bool IsHitAABBs(const AABB& box1, const AABB& box2);

bool IsSphereHitAABB(const Sphere& sphere, const AABB& aabb);

bool IsPointHitAABB(const Vector3& point, const AABB& aabb);

bool IsLineHitAABB(const Line& segment, const AABB& aabb);

bool IsRayHitAABB(const Ray& segment, const AABB& aabb);

bool IsSegmentHitAABB(const Segment& segment, const AABB& aabb);

bool IsSphereHitOBB(const Sphere& sphere, const OBB& obb, const Matrix4x4& obbObjectTransformMatrix);

bool IsSphereHitOBB(const Sphere& sphere, const OBB& obb);
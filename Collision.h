#pragma once

#include "Sphere.h"
#include "Plane.h"
#include "Line.h"
#include "Triangle.h"
#include "AABB.h"

bool IsHitSpheres(const Sphere& sphere1, const Sphere& sphere2);


bool IsSphereHitPlane(const Sphere& sphere, const Plane& plane);


bool IsLineHitPlane(const Line& line, const Plane& plane);

bool IsRayHitPlane(const Ray& ray, const Plane& plane);

bool IsSegmentHitPlane(const Segment& segment, const Plane& plane);


bool IsLineHitTriangle(const Line& line, const Triangle& triangle);

bool IsRayHitTriangle(const Ray& ray, const Triangle& triangle);

bool IsSegmentHitTriangle(const Segment& segment, const Triangle& triangle);

bool IsHitAABBs(const AABB& box1, const AABB& box2);
#pragma once

#include "Sphere.h"
#include "Plane.h"

bool IsHitSpheres(const Sphere& sphere1, const Sphere& sphere2);

bool IsSphereHitPlane(const Sphere& sphere, const Plane& plane);
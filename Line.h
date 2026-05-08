#pragma once
#include "Vector3.h"

struct Line {
	Vector3 origin;
	Vector3 difference;
};

struct Ray {
	Vector3 origin;
	Vector3 difference;
};

struct Segment {
	Vector3 origin;
	Vector3 difference;
};

inline Vector3 ClosestPoint(const Vector3& point, const Segment& segment){

	return segment.origin + VectorProjectClamped((point - segment.origin), segment.difference);

}
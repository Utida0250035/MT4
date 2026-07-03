#include "DrawShapes.h"
#include "NoviceUtility.h"
#include <Novice.h>
#include <cmath>
#include <numbers>
#include <stdint.h>

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {

	const float& kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / static_cast<float>(kSubdivision);

	for (size_t i = 0; i <= kSubdivision; ++i) {
		// グリッド線(Z軸平行)

		Vector3 lineStartPosWorld = Vector3{ -kGridHalfWidth + kGridEvery * static_cast<float>(i), 0.0f, -kGridHalfWidth };
		Vector3 lineEndPosWorld = Vector3{ lineStartPosWorld.x, 0.0f, kGridHalfWidth };

		Matrix4x4 lineStartWorldMatrix = MakeWorldMatrix(lineStartPosWorld);
		Matrix4x4 lineEndWorldMatrix = MakeWorldMatrix(lineEndPosWorld);

		Vector3 lineStartPosNdc = VectorTransform(Vector3{}, lineStartWorldMatrix * viewProjectionMatrix);
		Vector3 lineEndPosNdc = VectorTransform(Vector3{}, lineEndWorldMatrix * viewProjectionMatrix);

		Vector3 lineStartPosScreen = VectorTransform(lineStartPosNdc, viewportMatrix);
		Vector3 lineEndPosScreen = VectorTransform(lineEndPosNdc, viewportMatrix);

		NoviceUtility::DrawLine(
			lineStartPosScreen, lineEndPosScreen, 0xAAAAAAFF
		);

	}

	for (size_t i = 0; i <= kSubdivision; ++i) {
		// グリッド線(X軸平行)

		Vector3 lineStartPosWorld = Vector3{ -kGridHalfWidth, 0.0f, -kGridHalfWidth + kGridEvery * static_cast<float>(i) };
		Vector3 lineEndPosWorld = Vector3{ kGridHalfWidth, 0.0f, lineStartPosWorld.z };

		Matrix4x4 lineStartWorldMatrix = MakeWorldMatrix(lineStartPosWorld);
		Matrix4x4 lineEndWorldMatrix = MakeWorldMatrix(lineEndPosWorld);

		Vector3 lineStartPosNdc = VectorTransform(Vector3{}, lineStartWorldMatrix * viewProjectionMatrix);
		Vector3 lineEndPosNdc = VectorTransform(Vector3{}, lineEndWorldMatrix * viewProjectionMatrix);

		Vector3 lineStartPosScreen = VectorTransform(lineStartPosNdc, viewportMatrix);
		Vector3 lineEndPosScreen = VectorTransform(lineEndPosNdc, viewportMatrix);

		NoviceUtility::DrawLine(
			lineStartPosScreen, lineEndPosScreen, 0xAAAAAAFF
		);

	}

	// {x, 0, 0}
	Vector3 xLineStartPosWorld = Vector3{ -kGridHalfWidth, 0.0f, 0.0f };
	Vector3 xLineEndPosWorld = Vector3{ kGridHalfWidth, 0.0f, 0.0f };

	Matrix4x4 xLineStartWorldMatrix = MakeWorldMatrix(xLineStartPosWorld);
	Matrix4x4 xLineEndWorldMatrix = MakeWorldMatrix(xLineEndPosWorld);

	Vector3 xLineStartPosNdc = VectorTransform(Vector3{}, xLineStartWorldMatrix * viewProjectionMatrix);
	Vector3 xLineEndPosNdc = VectorTransform(Vector3{}, xLineEndWorldMatrix * viewProjectionMatrix);

	Vector3 xLineStartPosScreen = VectorTransform(xLineStartPosNdc, viewportMatrix);
	Vector3 xLineEndPosScreen = VectorTransform(xLineEndPosNdc, viewportMatrix);

	NoviceUtility::DrawLine(
		xLineStartPosScreen, xLineEndPosScreen, 0x000000FF
	);

	// {0, 0, z}
	Vector3 zLineStartPosWorld = Vector3{ 0.0f, 0.0f, -kGridHalfWidth };
	Vector3 zLineEndPosWorld = Vector3{ 0.0f, 0.0f, kGridHalfWidth };

	Matrix4x4 zLineStartWorldMatrix = MakeWorldMatrix(zLineStartPosWorld);
	Matrix4x4 zLineEndWorldMatrix = MakeWorldMatrix(zLineEndPosWorld);

	Vector3 zLineStartPosNdc = VectorTransform(Vector3{}, zLineStartWorldMatrix * viewProjectionMatrix);
	Vector3 zLineEndPosNdc = VectorTransform(Vector3{}, zLineEndWorldMatrix * viewProjectionMatrix);

	Vector3 zLineStartPosScreen = VectorTransform(zLineStartPosNdc, viewportMatrix);
	Vector3 zLineEndPosScreen = VectorTransform(zLineEndPosNdc, viewportMatrix);

	NoviceUtility::DrawLine(
		zLineStartPosScreen, zLineEndPosScreen, 0x000000FF
	);

}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, const uint32_t color) {

	const uint32_t kSubdivision = 8;
	const float kLonEvery = std::numbers::pi_v<float> *2.0f / static_cast<float>(kSubdivision);
	const float kLatEvery = std::numbers::pi_v<float> / static_cast<float>(kSubdivision);

	Matrix4x4 worldViewProjectionMatrix = MakeWorldMatrix(sphere.center) * viewProjectionMatrix;

	for (size_t i = 0; i < kSubdivision; ++i) {

		float lat = -(std::numbers::pi_v<float> *0.5f) + kLatEvery * static_cast<float>(i);

		for (size_t j = 0; j < kSubdivision; ++j) {

			float lon = static_cast<float>(j) * kLonEvery;

			Vector3 aPosLocal, bPosLocal, cPosLocal;

			aPosLocal = Vector3{ cos(lat) * cos(lon), sin(lat), cos(lat) * sin(lon) } * sphere.radius;

			bPosLocal = Vector3{ cos(lat + kLatEvery) * cos(lon), sin(lat + kLatEvery), cos(lat + kLatEvery) * sin(lon) } * sphere.radius;

			cPosLocal = Vector3{ cos(lat) * cos(lon + kLonEvery), sin(lat), cos(lat) * sin(lon + kLonEvery) } * sphere.radius;

			Vector3 lineABStartPosNdc = VectorTransform(aPosLocal, worldViewProjectionMatrix);
			Vector3 lineABEndPosNdc = VectorTransform(bPosLocal, worldViewProjectionMatrix);

			Vector3 lineABStartPosScreen = VectorTransform(lineABStartPosNdc, viewportMatrix);
			Vector3 lineABEndPosScreen = VectorTransform(lineABEndPosNdc, viewportMatrix);

			NoviceUtility::DrawLine(
				lineABStartPosScreen, lineABEndPosScreen, color
			);

			Vector3 lineACStartPosNdc = VectorTransform(aPosLocal, worldViewProjectionMatrix);
			Vector3 lineACEndPosNdc = VectorTransform(cPosLocal, worldViewProjectionMatrix);

			Vector3 lineACStartPosScreen = VectorTransform(lineACStartPosNdc, viewportMatrix);
			Vector3 lineACEndPosScreen = VectorTransform(lineACEndPosNdc, viewportMatrix);

			NoviceUtility::DrawLine(
				lineACStartPosScreen, lineACEndPosScreen, color
			);

		}


	}

}

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	// 矩形の中心を選定
	Vector3 planeCenter = plane.distance * plane.normal;

	// 平面の法線と垂直なベクトル4つ
	Vector3 perpendiculars[4];

	perpendiculars[0] = VectorNormalize(PerpendicularAny(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x, -perpendiculars[0].y, -perpendiculars[0].z };
	perpendiculars[2] = VectorCross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x, -perpendiculars[2].y, -perpendiculars[2].z };

	// 平面に含まれる矩形の4頂点
	Vector3 points[4]{};

	for (size_t i = 0; i < 4; ++i) {

		Vector3 extend = 2.0f * perpendiculars[i];
		Vector3 point = planeCenter + extend;
		points[i] = ScreenTransform(point, viewProjectionMatrix, viewportMatrix);

	}

	NoviceUtility::DrawLine(points[2], points[0], color);

	NoviceUtility::DrawLine(points[2], points[1], color);

	NoviceUtility::DrawLine(points[3], points[0], color);

	NoviceUtility::DrawLine(points[3], points[1], color);

}

void DrawLine(const Line& line, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const float virtualLength = 1.0f;

	Vector3 virtualEndPos = line.origin + VectorNormalize(line.difference) * virtualLength;

	Vector3 lineEndPosScreen[2] = {
		ScreenTransform(line.origin, viewProjectionMatrix, viewportMatrix),
		ScreenTransform(virtualEndPos, viewProjectionMatrix, viewportMatrix)
	};

	NoviceUtility::DrawLine(lineEndPosScreen[0], lineEndPosScreen[1], color);

}

void DrawRay(const Ray& ray, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	const float virtualLength = 1.0f;

	Vector3 virtualEndPos = ray.origin + VectorNormalize(ray.difference) * virtualLength;

	Vector3 lineEndPosScreen[2] = {
		ScreenTransform(ray.origin, viewProjectionMatrix, viewportMatrix),
		ScreenTransform(virtualEndPos, viewProjectionMatrix, viewportMatrix)
	};

	NoviceUtility::DrawLine(lineEndPosScreen[0], lineEndPosScreen[1], color);

	Sphere lineEndSphere = Sphere{ ray.origin, 0.05f };

	DrawSphere(lineEndSphere, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);

}

void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 endPos = segment.origin + segment.difference;

	Vector3 lineEndPosScreen[2] = {
		ScreenTransform(segment.origin, viewProjectionMatrix, viewportMatrix),
		ScreenTransform(endPos, viewProjectionMatrix, viewportMatrix)
	};

	NoviceUtility::DrawLine(lineEndPosScreen[0], lineEndPosScreen[1], color);

	Sphere lineEndSpheres[2] = {
		Sphere{segment.origin, 0.05f},
		Sphere{endPos, 0.05f}
	};

	for (const auto& sphere : lineEndSpheres) {

		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, 0xFFFFFFFF);

	}

}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 verticesScreen[3] = {
		ScreenTransform(triangle.vertices[0], viewProjectionMatrix, viewportMatrix),
		ScreenTransform(triangle.vertices[1], viewProjectionMatrix, viewportMatrix),
		ScreenTransform(triangle.vertices[2], viewProjectionMatrix, viewportMatrix),
	};

	Novice::DrawTriangle(
		static_cast<int>(verticesScreen[0].x), static_cast<int>(verticesScreen[0].y),
		static_cast<int>(verticesScreen[1].x), static_cast<int>(verticesScreen[1].y),
		static_cast<int>(verticesScreen[2].x), static_cast<int>(verticesScreen[2].y),
		color,
		kFillModeWireFrame
	);

}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 verticesScreen[8] = {
		// 右上奥
		ScreenTransform(aabb.max, viewProjectionMatrix, viewportMatrix),
		// 左上奥
		ScreenTransform(Vector3{aabb.min.x, aabb.max.y, aabb.max.z}, viewProjectionMatrix, viewportMatrix),
		// 左上手前
		ScreenTransform(Vector3{aabb.min.x, aabb.max.y, aabb.min.z}, viewProjectionMatrix, viewportMatrix),
		// 右上手前
		ScreenTransform(Vector3{aabb.max.x, aabb.max.y, aabb.min.z}, viewProjectionMatrix, viewportMatrix),

		// 右下奥
		ScreenTransform(Vector3{aabb.max.x, aabb.min.y, aabb.max.z}, viewProjectionMatrix, viewportMatrix),
		// 左下奥
		ScreenTransform(Vector3{aabb.min.x, aabb.min.y, aabb.max.z}, viewProjectionMatrix, viewportMatrix),
		// 左下手前
		ScreenTransform(aabb.min, viewProjectionMatrix, viewportMatrix),
		// 右下手前
		ScreenTransform(Vector3{aabb.max.x, aabb.min.y, aabb.min.z}, viewProjectionMatrix, viewportMatrix),
	};

	NoviceUtility::DrawLine(verticesScreen[0], verticesScreen[1], color);
	NoviceUtility::DrawLine(verticesScreen[1], verticesScreen[2], color);
	NoviceUtility::DrawLine(verticesScreen[2], verticesScreen[3], color);
	NoviceUtility::DrawLine(verticesScreen[3], verticesScreen[0], color);
	NoviceUtility::DrawLine(verticesScreen[4], verticesScreen[5], color);
	NoviceUtility::DrawLine(verticesScreen[5], verticesScreen[6], color);
	NoviceUtility::DrawLine(verticesScreen[6], verticesScreen[7], color);
	NoviceUtility::DrawLine(verticesScreen[7], verticesScreen[4], color);
	NoviceUtility::DrawLine(verticesScreen[0], verticesScreen[4], color);
	NoviceUtility::DrawLine(verticesScreen[1], verticesScreen[5], color);
	NoviceUtility::DrawLine(verticesScreen[2], verticesScreen[6], color);
	NoviceUtility::DrawLine(verticesScreen[3], verticesScreen[7], color);

}

void DrawOBB(const OBB& obb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 scaledAxis[3] = { obb.axis[0] * obb.size.x * 0.5f, obb.axis[1] * obb.size.y * 0.5f, obb.axis[2] * obb.size.z * 0.5f };

	Vector3 verticesScreen[8] = {
		// 右上奥
		ScreenTransform(obb.center + scaledAxis[0] + scaledAxis[1] + scaledAxis[2], viewProjectionMatrix, viewportMatrix),
		// 左上奥
		ScreenTransform(obb.center - scaledAxis[0] + scaledAxis[1] + scaledAxis[2], viewProjectionMatrix, viewportMatrix),
		// 左上手前
		ScreenTransform(obb.center - scaledAxis[0] + scaledAxis[1] - scaledAxis[2], viewProjectionMatrix, viewportMatrix),
		// 右上手前
		ScreenTransform(obb.center + scaledAxis[0] + scaledAxis[1] - scaledAxis[2], viewProjectionMatrix, viewportMatrix),

		// 右下奥
		ScreenTransform(obb.center + scaledAxis[0] - scaledAxis[1] + scaledAxis[2], viewProjectionMatrix, viewportMatrix),
		// 左下奥
		ScreenTransform(obb.center - scaledAxis[0] - scaledAxis[1] + scaledAxis[2], viewProjectionMatrix, viewportMatrix),
		// 左下手前
		ScreenTransform(obb.center - scaledAxis[0] - scaledAxis[1] - scaledAxis[2], viewProjectionMatrix, viewportMatrix),
		// 右下手前
		ScreenTransform(obb.center + scaledAxis[0] - scaledAxis[1] - scaledAxis[2], viewProjectionMatrix, viewportMatrix),
	};

	NoviceUtility::DrawLine(verticesScreen[0], verticesScreen[1], color);
	NoviceUtility::DrawLine(verticesScreen[1], verticesScreen[2], color);
	NoviceUtility::DrawLine(verticesScreen[2], verticesScreen[3], color);
	NoviceUtility::DrawLine(verticesScreen[3], verticesScreen[0], color);

	NoviceUtility::DrawLine(verticesScreen[4], verticesScreen[5], color);
	NoviceUtility::DrawLine(verticesScreen[5], verticesScreen[6], color);
	NoviceUtility::DrawLine(verticesScreen[6], verticesScreen[7], color);
	NoviceUtility::DrawLine(verticesScreen[7], verticesScreen[4], color);

	NoviceUtility::DrawLine(verticesScreen[0], verticesScreen[4], color);
	NoviceUtility::DrawLine(verticesScreen[1], verticesScreen[5], color);
	NoviceUtility::DrawLine(verticesScreen[2], verticesScreen[6], color);
	NoviceUtility::DrawLine(verticesScreen[3], verticesScreen[7], color);

}

void DrawBezier2(const Bezier2& bezier, const uint32_t division, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	if (division == 0) {

		assert(false);

		return;

	}

	const float segmantRatio = 1.0f / static_cast<float>(division);

	float t = 0.0f;

	Vector3 p0p1{};
	Vector3 p1p2{};

	Vector3 segmentStart = bezier.p[0];
	Vector3 segmentEnd{};

	Vector3 screenPos0{};
	Vector3 screenPos1{};

	for (const auto& p : bezier.p) {

		DrawSphere(Sphere{ p, 0.01f }, viewProjectionMatrix, viewportMatrix, WHITE);

	}

	while (t <= 1.0f) {

		t += segmantRatio;

		p0p1 = Lerp(bezier.p[0], bezier.p[1], t);
		p1p2 = Lerp(bezier.p[1], bezier.p[2], t);
		segmentEnd = Lerp(p0p1, p1p2, t);

		screenPos0 = ScreenTransform(segmentStart, viewProjectionMatrix, viewportMatrix);
		screenPos1 = ScreenTransform(segmentEnd, viewProjectionMatrix, viewportMatrix);

		segmentStart = segmentEnd;

		NoviceUtility::DrawLine(screenPos0, screenPos1, color);

	}

}

void DrawCatmullRom3(const CatmullRom3& spline, const uint32_t division, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	if (division == 0) {

		assert(false);

		return;

	}

	const float segmantRatio = 1.0f / static_cast<float>(division);

	float t = 0.0f;

	Vector3 segmentStart = spline.p[1];
	Vector3 segmentEnd{};

	Vector3 screenPos0{};
	Vector3 screenPos1{};

	for (const auto& p : spline.p) {

		DrawSphere(Sphere{ p, 0.01f }, viewProjectionMatrix, viewportMatrix, WHITE);

	}

	while (t < 1.0f) {

		t += segmantRatio;

		if (t >= 1.0f) {

			t = 1.0f;

		}

		segmentEnd = 0.5f * ((-spline.p[0] + 3.0f * spline.p[1] - 3.0f * spline.p[2] + spline.p[3]) * t * t * t +
			(2.0f * spline.p[0] - 5.0f * spline.p[1] + 4.0f * spline.p[2] - spline.p[3]) * t * t +
			(-spline.p[0] + spline.p[2]) * t + 2.0f * spline.p[1]);

		screenPos0 = ScreenTransform(segmentStart, viewProjectionMatrix, viewportMatrix);
		screenPos1 = ScreenTransform(segmentEnd, viewProjectionMatrix, viewportMatrix);

		segmentStart = segmentEnd;

		NoviceUtility::DrawLine(screenPos0, screenPos1, color);

	}

}


void DrawSpring(const Spring& spring, const Ball& weight, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 anchorScreenPos = ScreenTransform(spring.anchor, viewProjectionMatrix, viewportMatrix);

	Vector3 weightScreenPos = ScreenTransform(weight.position, viewProjectionMatrix, viewportMatrix);

	NoviceUtility::DrawLine(anchorScreenPos, weightScreenPos, color);
	DrawSphere(Sphere{weight.position, weight.radius}, viewProjectionMatrix, viewportMatrix, color);

}

void DrawPendulum(const Pendulum& pendulum, const Ball& bob, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 anchorScreenPos = ScreenTransform(pendulum.anchorPos, viewProjectionMatrix, viewportMatrix);

	Vector3 weightScreenPos = ScreenTransform(bob.position, viewProjectionMatrix, viewportMatrix);

	NoviceUtility::DrawLine(anchorScreenPos, weightScreenPos, color);
	DrawSphere(Sphere{ bob.position, bob.radius }, viewProjectionMatrix, viewportMatrix, color);

}

void DrawConicalPendulum(const ConicalPendulum& conicalPendulum, const Ball& bob, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {

	Vector3 bobScreenPos = ScreenTransform(conicalPendulum.anchorPos, viewProjectionMatrix, viewportMatrix);

	Vector3 weightScreenPos = ScreenTransform(bob.position, viewProjectionMatrix, viewportMatrix);

	NoviceUtility::DrawLine(bobScreenPos, weightScreenPos, color);
	DrawSphere(Sphere{ bob.position, bob.radius }, viewProjectionMatrix, viewportMatrix, color);

}
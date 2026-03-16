#include "DrawShapes.h"
#include "NoviceUtility.h"
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

	const uint32_t kSubdivision = 12;
	const float kLonEvery = std::numbers::pi_v<float> *2.0f / static_cast<float>(kSubdivision);
	const float kLatEvery = std::numbers::pi_v<float> / static_cast<float>(kSubdivision);

	Matrix4x4 worldViewProjectionMatrix = MakeWorldMatrix(sphere.center) * viewProjectionMatrix;

	for (size_t i = 0; i < kSubdivision; ++i) {

		float lat = std::numbers::pi_v<float> *0.5f + kLatEvery * static_cast<float>(i);

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
#include "SphericalCoordinate.h"
#include "Matrix3D.h"
#include <cMath>
#include <numbers>
#include <algorithm>
#include <ImGui.h>

Vector3 Spherical::ToCartesian() const {

	float rho = radius * std::cos(theta);

	return {
		rho * std::cos(phi),
		radius * std::sin(theta),
		rho * std::sin(phi)
	};

}

void Spherical::Imgui() {

	ImGui::DragFloat3("Spherical", &this->radius, 0.001f);

	const float limit = std::numbers::pi_v<float> *0.5f - 0.01f;

	radius = std::max(radius, 0.1f);
	theta = std::clamp(theta, -limit, limit);

}

Matrix4x4 Spherical::CameraMatrix(const Vector3& target) const {

	Vector3 offset = ToCartesian();

	Vector3 eye = target + offset;

	Vector3 worldUp{ 0.0f, 1.0f ,0.0f };

	Vector3 forward = VectorNormalize(target - eye);
	Vector3 right = VectorNormalize(VectorCross(worldUp, forward));
	Vector3 up = VectorNormalize(VectorCross(forward, right));

	return { {
		{right.x, right.y, right.z, 0.0f},
		{up.x, up.y, up.z, 0.0f},
		{forward.x, forward.y, forward.z, 0.0f},
		{eye.x, eye.y, eye.z, 1.0f}
	} };

}
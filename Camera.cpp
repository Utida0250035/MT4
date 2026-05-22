#include "Camera.h"

#include <Novice.h>
#include <ImGui.h>

void Camera::Update() {

	this->MoveInput();

	this->Move();

	worldMatrix_ = MakeWorldMatrix(translate_, scale_, rotate_);
	viewMatrix_ = Inverse(worldMatrix_);
	projectionMatrix_ = MakePerspectiveFovMatrix(fovY_, viewportWidth_ / viewportHeight_, nearClip_, farClip_);
	viewProjectionMatrix_ = viewMatrix_ * projectionMatrix_;
	viewportMatrix_ = MakeViewportMatrix(0.0f, 0.0f, viewportWidth_, viewportHeight_, minDepth_, maxDepth_);

}

void Camera::MoveInput() {

	if (ImGui::GetIO().WantCaptureMouse) {

		return;

	}

	velocity_ = Vector3{};
	angularVelocity_ = Vector3{};

	preCursorPos_ = cursorPos_;

	int cursorX;
	int cursorY;

	Novice::GetMousePosition(&cursorX, &cursorY);

	cursorPos_ = Vector2{ static_cast<float>(cursorX), static_cast<float>(cursorY) };

	Vector2 diff = cursorPos_ - preCursorPos_;
	
	// 視覚と合わせるためにY軸のみ符号を反転
	Matrix4x4 rotateMatrix = MakeRotateMatrix(Vector3{ rotate_.x, -rotate_.y, rotate_.z });

	if (Novice::IsPressMouse(0)) {

		velocity_ = { diff.x * 0.03125f * 0.5f, -diff.y * 0.03125f * 0.5f, 0.0f };

	} else {

		velocity_ = { 0.0f, 0.0f, static_cast<float>(Novice::GetWheel()) * 0.03125f * 0.5f };

		if (Novice::IsPressMouse(1)) {

			angularVelocity_ = { diff.y * 0.03125f * 0.5f, diff.x * 0.03125f * 0.5f, 0.0f };

		}

	}

	velocity_ = Transform(velocity_, rotateMatrix);

}


void Camera::Move() {

	rotate_ += angularVelocity_;

	translate_ += velocity_;

}
#include "Camera.h"

void Camera::MatrixUpdate() {

	cameraWorldMatrix_ = MakeWorldMatrix(translate_, scale_, rotate_);
	viewMatrix_ = Inverse(cameraWorldMatrix_);
	projectionMatrix_ = MakePerspectiveFovMatrix(fovY_, viewportWidth_ / viewportHeight_, nearClip_, farClip_);
	viewProjectionMatrix_ = viewMatrix_ * projectionMatrix_;
	viewportMatrix_ = MakeViewportMatrix(0.0f, 0.0f, viewportWidth_, viewportHeight_, minDepth_, maxDepth_);

}

Vector3 Camera::Transform(const Vector3& translate, const Vector3& scale = { 1.0f, 1.0f, 1.0f }, const Vector3& rotate = { 0.0f, 0.0f, 0.0f }) {



}
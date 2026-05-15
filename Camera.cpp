#include "Camera.h"

void Camera::MatrixUpdate() {

	worldMatrix_ = MakeWorldMatrix(translate_, scale_, rotate_);
	viewMatrix_ = Inverse(worldMatrix_);
	projectionMatrix_ = MakePerspectiveFovMatrix(fovY_, viewportWidth_ / viewportHeight_, nearClip_, farClip_);
	viewProjectionMatrix_ = viewMatrix_ * projectionMatrix_;
	viewportMatrix_ = MakeViewportMatrix(0.0f, 0.0f, viewportWidth_, viewportHeight_, minDepth_, maxDepth_);

}
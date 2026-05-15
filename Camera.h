#pragma once
#include "Matrix3D.h"

class Camera {

private:

	float viewportWidth_ = 1280.0f;

	float viewportHeight_ = 720.0f;

	float fovY_ = 0.45f;

	float nearClip_ = 0.1f;

	float farClip_ = 100.0f;

	float minDepth_ = 0.0f;

	float maxDepth_ = 1.0f;

	// 拡大縮小
	Vector3 scale_{ 1.0f, 1.0f, 1.0f };

	// 位置
	Vector3 translate_{};

	// 回転
	Vector3 rotate_{};

	// ワールド行列
	Matrix4x4 worldMatrix_{};

	// ビュー行列
	Matrix4x4 viewMatrix_{};

	// 透視投影行列
	Matrix4x4 projectionMatrix_{};

	// ビュー行列 * 透視投影行列
	Matrix4x4 viewProjectionMatrix_{};

	// ビューポート変換行列
	Matrix4x4 viewportMatrix_{};

public:

	/// <summary>
	/// 行列の更新
	/// </summary>
	void MatrixUpdate();

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns>ビュー行列 * 透視投影行列</returns>
	Matrix4x4 GetViewProjectionMatrix()const { return viewProjectionMatrix_; }

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns>ビューポート変換行列</returns>
	Matrix4x4 GetViewportMatrix()const { return viewportMatrix_; }

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns> 位置 </returns>
	Vector3 GetTranslate()const { return translate_; }

	/// <summary>
	/// ゲッター
	/// </summary>
	/// <returns> 回転 </returns>
	Vector3 GetRotate()const { return rotate_; }

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="translate"> 位置 </param>
	void SetTranslate(const Vector3& translate) { translate_ = translate; }

	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="rotate"> 回転 </param>
	void SetRotate(const Vector3& rotate) { rotate_ = rotate; }

};
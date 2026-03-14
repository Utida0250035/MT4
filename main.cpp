#define NOMINMAX

#include "Matrix3D.h"
#include <Novice.h>
#include <numbers>
#include <cmath>
#include <algorithm>

// 個人: クラス記号_出席番号_氏_名_タイトル
// チーム: チームNo_タイトル
const char kWindowTitle[] = "LC1A_01_ウチダ_コウタ_MT3";

const float kWindowWidth = 1280.0f;
const float kWindowHeight = 720.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 cross = VectorCross(Vector3{ 1.2f, -3.9f, 2.5f }, Vector3{ 2.8f, 0.4f, -1.3f });

	const Vector3 kLocalVertices[3] = {
		Vector3{0.0f, 32.0f, 0.0f},
		Vector3{16.0f, -32.0f, 0.0f},
		Vector3{-16.0f, -32.0f, 0.0f}
	};

	float speed = 5.0f;

	Vector3 angularVelocity = Vector3{0.0f, std::numbers::pi_v<float> / 180.0f * 5.0f, 0.0f};

	Vector3 rotate{0.0f, 0.0f, 0.0f};
	Vector3 translate{0.0f, 0.0f, 0.0f};
	
	Vector3 cameraPosition{0.0f, 0.0f, -512.0f};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		if (keys[DIK_W]) {

			translate.z += speed;

		}

		if (keys[DIK_S]) {

			translate.z -= speed;

		}

		if (keys[DIK_D]) {

			translate.x += speed;

		}

		if (keys[DIK_A]) {

			translate.x -= speed;

		}

		translate.z = std::max(0.0f, translate.z);

		rotate += angularVelocity;

		if (rotate.y >= 2.0f * std::numbers::pi_v<float>) {

			rotate.y = fmodf(rotate.y, 2.0f * std::numbers::pi_v<float>);

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Matrix4x4 worldMatrix = MakeWorldMatrix(translate, Vector3{ 1.0f, 1.0f, 1.0f }, rotate);

		Matrix4x4 cameraMatrix = MakeWorldMatrix(cameraPosition, Vector3{ 1.0f, 1.0f, 1.0f }, Vector3{0.0f, 0.0f, 0.0f});

		Matrix4x4 viewMatrix = MatrixInverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MakePerspactiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);

		Matrix4x4 worldViewProjectionMatrix = worldMatrix * viewMatrix * projectionMatrix;

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		Vector3 screenVertices[3];
		for (size_t i = 0; i < 3; ++i) {

			Vector3 ndcVertex = VectorTransform(kLocalVertices[i], worldViewProjectionMatrix);

			screenVertices[i] = VectorTransform(ndcVertex, viewportMatrix);

		}

		Novice::DrawTriangle(
			static_cast<int>(screenVertices[0].x), static_cast<int>(screenVertices[0].y),
			static_cast<int>(screenVertices[1].x), static_cast<int>(screenVertices[1].y),
			static_cast<int>(screenVertices[2].x), static_cast<int>(screenVertices[2].y),
			RED,
			kFillModeSolid
		);

		VectorScreenPrintf(0, 0, cross, "Cross");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (!preKeys[DIK_ESCAPE] && keys[DIK_ESCAPE]) {
		
			break;
		
		}

	}

	///
	/// 終了処理
	///

	// ライブラリの終了
	Novice::Finalize();
	return 0;

}

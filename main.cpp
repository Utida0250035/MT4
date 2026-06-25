#include "AABB.h"
#include "Bezier.h"
#include "NoviceUtility.h"
#include "Camera.h"
#include "Collision.h"
#include "DrawShapes.h"
#include "Line.h"
#include "Matrix3D.h"
#include "OBB.h"
#include "Sphere.h"
#include "Transform.h"
#include <algorithm>
#include <cmath>
#include <ImGui.h>
#include <memory>
#include <Novice.h>
#include <numbers>
#include <string>

// 個人: クラス記号_出席番号_氏_名_タイトル
// チーム: チームNo_タイトル
const char kWindowTitle[] = "LE2A_02_ウチダ_コウタ_MT3";

const float kWindowWidth = 1280.0f;
const float kWindowHeight = 720.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<Camera> camera = nullptr;
	camera.reset(new Camera());

	camera->SetTranslate(Vector3{ 0.0f, 1.9f, -6.49f });

	camera->SetRotate(Vector3{ 0.26f, 0.0f, 0.0f });

	Vector3 cameraPosition{};
	Vector3 cameraRotate{};

	Transform transforms[3]{};
	Matrix4x4 worldMatrixs[3]{};

	bool isHit = false;

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

		ImGui::Begin("camera");

		cameraPosition = camera->GetTranslate();
		ImGui::DragFloat3("cameraTranslate", &cameraPosition.x, 0.0625f);
		camera->SetTranslate(cameraPosition);

		cameraRotate = camera->GetRotate();
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.0625f);
		camera->SetRotate(cameraRotate);

		ImGui::End();


		ImGui::Begin("transforms");

		const char* text[3] = {
			"transform0",
			"transform1",
			"transform2"
		};

		Matrix4x4 bufferMatrix = MakeIdentity4x4();

		std::string bufferStr{};

		for (size_t i = 0; i < 3; i++) {

			ImGui::Text(text[i]);

			bufferStr = "scale" + std::to_string(i);

			ImGui::DragFloat3(bufferStr.c_str(), &transforms[i].scale.x, 0.03125f);

			bufferStr = "rotate" + std::to_string(i);

			ImGui::DragFloat3(bufferStr.c_str(), &transforms[i].rotate.x, 0.03125f);

			bufferStr = "translate" + std::to_string(i);

			ImGui::DragFloat3(bufferStr.c_str(), &transforms[i].translate.x, 0.03125f);

			worldMatrixs[i] = MakeWorldMatrix(transforms[i]) * bufferMatrix;

			bufferMatrix = worldMatrixs[i];

		}

		ImGui::End();

		camera->Update();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		uint32_t objectsColor = BLACK;

		if (isHit) {

			objectsColor = RED;

		}

		const uint32_t colors[3] = {
			RED, GREEN, BLUE
		};

		for (size_t i = 0; i < 3; i++) {

			const auto& mat = worldMatrixs[i].m;

			DrawSphere(Sphere{ Vector3{mat[3][0], mat[3][1], mat[3][2]}, 0.1f }, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), colors[i]);

		}

		Vector3 screenPos0{};
		Vector3 screenPos1{};

		for (size_t i = 1; i < 3; i++) {

			const auto& mat0 = worldMatrixs[i - 1].m;
			const auto& mat1 = worldMatrixs[i].m;

			screenPos0 = ScreenTransform(Vector3{ mat0[3][0], mat0[3][1], mat0[3][2] }, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

			screenPos1 = ScreenTransform(Vector3{ mat1[3][0], mat1[3][1], mat1[3][2] }, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

			NoviceUtility::DrawLine(screenPos0, screenPos1, WHITE);

		}

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

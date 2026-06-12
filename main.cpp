#include "AABB.h"
#include "Camera.h"
#include "Collision.h"
#include "DrawShapes.h"
#include "Line.h"
#include "Matrix3D.h"
#include "OBB.h"
#include "Sphere.h"
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

	OBB box{
		.center = {0.5f, 0.5f, 0.5f},
		.axis = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}},
		.size = {1.0f, 1.0f, 1.0f},
	};

	Vector3 boxRotate{};

	Sphere sphere{
		.center{1.0f, 1.0f, 1.0f},
		.radius = 0.5f
	};

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

		camera->Update();


		ImGui::Begin("sphere");

		ImGui::DragFloat3("center", &sphere.center.x, 0.03125f);

		ImGui::DragFloat("radius", &sphere.radius, 0.03125f);

		ImGui::End();


		ImGui::Begin("box");

		ImGui::DragFloat3("size", &box.size.x, 0.03125f);

		ImGui::DragFloat3("rotate", &boxRotate.x, 0.03125f);

		if (ImGui::IsItemActive()) {

			SetObbAxis(box, boxRotate);

		}

		ImGui::DragFloat3("translate", &box.center.x, 0.03125f);

		ImGui::End();

		isHit = IsSphereHitOBB(sphere, box);

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

		DrawSphere(sphere, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), objectsColor);

		DrawOBB(box, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), objectsColor);

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

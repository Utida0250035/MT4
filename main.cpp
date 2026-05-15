#include "Camera.h"
#include "DrawShapes.h"
#include "Matrix3D.h"
#include "Sphere.h"
#include "Line.h"
#include "NoviceUtility.h"
#include <algorithm>
#include <cmath>
#include <Novice.h>
#include <numbers>
#include <ImGui.h>
#include <memory>

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

	Segment segment{ {-2.0f, -1.0f, 0.0f}, {3.0f, 2.0f, 2.0f} };

	Vector3 point{ -1.5f, 0.6f, 0.6f };

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

		// pointを線分に投影したベクトル
		Vector3 project = VectorProject(point - segment.origin, segment.difference);

		// pointに対する線分上の最近接点
		Vector3 closestPoint = ClosestPoint(point, segment);

		Sphere pointSphere{ point, 0.01f };

		Sphere closestPointSphere{ closestPoint, 0.01f };

		ImGui::Begin("debug");

		cameraPosition = camera->GetTranslate();
		ImGui::DragFloat3("cameraTranslate", &cameraPosition.x, 0.0625f);
		camera->SetTranslate(cameraPosition);

		cameraRotate = camera->GetRotate();
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.0625f);
		camera->SetRotate(cameraRotate);

		ImGui::Text("Project: (%8.3f, %8.3f, %8.3f)", project.x, project.y, project.z);

		ImGui::End();

		camera->MatrixUpdate();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		Vector3 start = Transform(Transform(segment.origin, camera->GetViewProjectionMatrix()), camera->GetViewportMatrix());

		Vector3 end = Transform(Transform(segment.origin + segment.difference, camera->GetViewProjectionMatrix()), camera->GetViewportMatrix());

		NoviceUtility::DrawLine(start, end, WHITE);

		DrawSphere(pointSphere, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), RED);

		DrawSphere(closestPointSphere, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), BLACK);

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

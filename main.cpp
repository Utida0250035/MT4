#include "AABB.h"
#include "Ball.h"
#include "Bezier.h"
#include "Camera.h"
#include "Collision.h"
#include "ConicalPendulum.h"
#include "DeltaTime.h"
#include "DrawShapes.h"
#include "Line.h"
#include "Matrix3D.h"
#include "Movement.h"
#include "NoviceUtility.h"
#include "OBB.h"
#include "Pendulum.h"
#include "Sphere.h"
#include "Spring.h"
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

	std::unique_ptr<DebugCamera> camera = std::make_unique<DebugCamera>();

	camera->SetTranslate(Vector3{ 0.0f, 1.9f, -6.49f });

	camera->SetRotate(Vector3{ 0.26f, 0.0f, 0.0f });

	Vector3 cameraPosition{};
	Vector3 cameraRotate{};

	Ball bobBall{};
	bobBall.radius = 0.1f;
	bobBall.mass = 1.0f;
	bobBall.color = BLUE;

	ConicalPendulum conicalPendulum{};
	conicalPendulum.anchorPos = { 0.0f, 1.5f, 0.0f };
	conicalPendulum.length = 1.0f;
	conicalPendulum.angle = 45.0f * std::numbers::pi_v<float> / 180.0f;
	conicalPendulum.halfApexAngle = 80.0f * std::numbers::pi_v<float> / 180.0f;

	Vector3 gravity = { 0.0f, -8.0f, 0.0f };

	std::unique_ptr<DeltaTime> timeManager = std::make_unique<DeltaTime>();

	float deltaTime = 0.0f;

	bool isMove = false;

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

		timeManager->CalcDeltaTime();
		deltaTime = timeManager->GetDeltaTime();

		ImGui::Begin("camera");

		cameraPosition = camera->GetTranslate();
		ImGui::DragFloat3("cameraTranslate", &cameraPosition.x, 0.0625f);
		camera->SetTranslate(cameraPosition);

		cameraRotate = camera->GetRotate();
		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.0625f);
		camera->SetRotate(cameraRotate);

		ImGui::End();

		camera->Update();

		ImGui::Begin("pendulum");

		ImGui::SmallButton("start");

		if (ImGui::IsItemActivated()) {

			if (!isMove) {

				isMove = true;

			}

		}

		ImGui::Text("pendulum");

		ImGui::DragFloat3("anchorPos", &conicalPendulum.anchorPos.x, 0.03125f);
		ImGui::DragFloat("length", &conicalPendulum.length, 0.03125f);

		if (ImGui::IsItemActive()) {

			conicalPendulum.length = std::max(0.5f, conicalPendulum.length);

		}

		float angleDegree = conicalPendulum.angle / std::numbers::pi_v<float> * 180.0f;

		ImGui::DragFloat("angle(deg)", &angleDegree, 0.25f);

		if (ImGui::IsItemActive()) {

			conicalPendulum.angularVelocity = 0.0f;
			conicalPendulum.angle = angleDegree * std::numbers::pi_v<float> / 180.0f;

		}

		ImGui::Text("weight");

		ImGui::DragFloat3("weightPos", &bobBall.position.x);
		ImGui::DragFloat3("velocity", &bobBall.velocity.x);
		ImGui::Text("magnitude: %f", VectorLength(bobBall.velocity));
		ImGui::DragFloat3("acceleration", &bobBall.acceleration.x);
		ImGui::Text("magnitude: %f", VectorLength(bobBall.acceleration));

		ImGui::End();

		if (isMove) {

			ConicalPendulumBallMovement2D(conicalPendulum, bobBall, gravity.y, deltaTime);

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		DrawConicalPendulum(conicalPendulum, bobBall, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), bobBall.color);

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

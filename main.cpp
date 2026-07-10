#include "AABB.h"
#include "Ball.h"
#include "Bezier.h"
#include "Camera.h"
#include "Collision.h"
#include "DeltaTime.h"
#include "DrawShapes.h"
#include "Line.h"
#include "Matrix3D.h"
#include "Movement.h"
#include "NoviceUtility.h"
#include "OBB.h"
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

	Ball ball{};
	ball.radius = 0.1f;
	ball.mass = 1.0f;
	ball.bounciness = 0.8f;
	ball.position = { 1.0f, 1.0f, 0.0f };
	ball.color = BLUE;

	Plane plane{};
	plane.normal = { 0.0f, 1.0f, 0.0f };

	Vector3 gravity = { 0.0f, -20.0f, 0.0f };

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

		ImGui::Begin("ball");

		ImGui::SmallButton("isMove");

		if (ImGui::IsItemActivated()) {

			isMove = !isMove;

		}

		ImGui::SameLine();

		ImGui::Text(isMove ? "on" : "off");

		ImGui::SmallButton("reset");

		if (ImGui::IsItemActivated()) {

			ball.acceleration = {};
			ball.velocity = {};
			ball.position = {};

		}

		ImGui::DragFloat3("ballPos", &ball.position.x, 0.03125f);

		ImGui::DragFloat3("ballVelocity", &ball.velocity.x, 0.03125f);

		ImGui::DragFloat("ballBounciness", &ball.bounciness, 0.03125f);

		ImGui::End();

		ImGui::Begin("plane");

		ImGui::DragFloat("distance", &plane.distance, 0.03125f);

		ImGui::DragFloat3("normal", &plane.normal.x, 0.03125f);

		if (ImGui::IsItemActive()) {

			plane.normal = VectorNormalize(plane.normal);

		}

		ImGui::End();

		if (isMove) {

			ball.acceleration = gravity;
			ball.velocity += ball.acceleration * deltaTime;
			ball.position += ball.velocity * deltaTime;

			BallReflectPlane(ball, plane, ball.bounciness, deltaTime);

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		DrawPlane(plane, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), BLACK);

		DrawSphere(Sphere{ ball.position, ball.radius }, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), RED);

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

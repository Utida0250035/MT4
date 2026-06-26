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

	std::unique_ptr<Camera> camera = std::make_unique<Camera>();

	camera->SetTranslate(Vector3{ 0.0f, 1.9f, -6.49f });

	camera->SetRotate(Vector3{ 0.26f, 0.0f, 0.0f });

	Vector3 cameraPosition{};
	Vector3 cameraRotate{};

	Vector3 gravity = { 0.0f, -9.8f, 0.0f };

	Ball weightBall{};
	weightBall.radius = 0.1f;
	weightBall.mass = 1.0f;
	weightBall.position = { 1.0f, 1.0f, 0.0f };
	weightBall.color = BLUE;

	Spring spring{};
	spring.anchor = { 0.0f, 1.0f, 0.0f };
	spring.naturalLength = 0.5f;
	spring.stiffness = 100.0f;
	spring.dampingCoefficient = 2.0f;

	std::unique_ptr<DeltaTime> timeManager = std::make_unique<DeltaTime>();

	float deltaTime = 0.0f;

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

		ImGui::Begin("spring");

		ImGui::Text("spring");

		ImGui::DragFloat3("anchorPos", &spring.anchor.x, 0.03125f);
		ImGui::DragFloat("naturalLength", &spring.naturalLength, 0.03125f);
		ImGui::DragFloat("stiffness", &spring.stiffness);
		ImGui::DragFloat("dampingCoefficient", &spring.dampingCoefficient, 0.03125f);

		ImGui::Text("weight");

		ImGui::DragFloat3("weightPos", &weightBall.position.x);
		ImGui::DragFloat("weightMass", &weightBall.mass);
		
		if (weightBall.mass <= 0.5f) {

			weightBall.mass = 0.5f;

		}

		ImGui::End();

		camera->Update();

		SpringBallMovement(spring, weightBall, gravity, deltaTime);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		DrawSpring(spring, weightBall, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), weightBall.color);

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

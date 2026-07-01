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

	Sphere moveSphere{};
	moveSphere.radius = 0.1f;
	Vector3 origin{};

	float angularVel = std::numbers::pi_v<float>;
	float angle = 0.0f;
	float orbitRadius = 0.75f;
	Vector3 velocity{};
	Vector3 acceleration{};


	Vector3 a{ 0.2f, 1.0f, 0.0f };
	Vector3 b{ 2.4f, 3.1f, 1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 rotate{ 0.4f, 1.43f, -0.8f };
	Matrix4x4 xRotateMatrix = MakeXRotateMatrix(rotate.x);
	Matrix4x4 yRotateMatrix = MakeYRotateMatrix(rotate.y);
	Matrix4x4 zRotateMatrix = MakeZRotateMatrix(rotate.z);
	Matrix4x4 rotateMatrix = xRotateMatrix * yRotateMatrix * zRotateMatrix;

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

		ImGui::Begin("circularMotion");

		ImGui::SmallButton("begin");

		if (ImGui::IsItemActivated()) {

			if (!isMove) {

				isMove = true;

			}

		}

		if (isMove) {

			angle += angularVel * deltaTime;

			moveSphere.center = {
				origin.x + std::cos(angle) * orbitRadius,
				origin.y + std::sin(angle) * orbitRadius,
				origin.z
			};

			velocity = {
				-orbitRadius * angularVel * std::sin(angle),
				orbitRadius * angularVel * std::cos(angle),
				0.0f
			};

			acceleration = {
				-orbitRadius * angularVel * angularVel * std::cos(angle),
				-orbitRadius * angularVel * angularVel * std::sin(angle),
				0.0f
			};

		}

		ImGui::DragFloat3("velocity", &velocity.x);
		ImGui::DragFloat3("acceleration", &acceleration.x);

		ImGui::End();

		ImGui::Begin("Window");

		Vector3 bufferVector = c;
		ImGui::DragFloat3("c", &bufferVector.x);

		bufferVector = d;
		ImGui::DragFloat3("d", &bufferVector.x);

		bufferVector = e;
		ImGui::DragFloat3("e", &bufferVector.x);


		ImGui::Text("matrix:");

		for (const auto& m : rotateMatrix.m) {

			ImGui::Text(" %f, %f, %f, %f", m[0], m[1], m[2], m[3]);

		}

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(camera->GetViewProjectionMatrix(), camera->GetViewportMatrix());

		DrawSphere(moveSphere, camera->GetViewProjectionMatrix(), camera->GetViewportMatrix(), GREEN);

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

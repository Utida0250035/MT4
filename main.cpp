#include "AABB.h"
#include "Ball.h"
#include "Bezier.h"
#include "Camera.h"
#include "Collision.h"
#include "DeltaTime.h"
#include "DrawShapes.h"
#include "Line.h"
#include "MathImGui.h"
#include "Matrix3D.h"
#include "Movement.h"
#include "NoviceUtility.h"
#include "OBB.h"
#include "Quaternion.h"
#include "Slope.h"
#include "Sphere.h"
#include "SphericalCoordinate.h"
#include "Spring.h"
#include "Transform.h"
#include "Unit.h"
#include "Vector2.h"
#include <algorithm>
#include <cmath>
#include <ImGui.h>
#include <memory>
#include <Novice.h>
#include <numbers>
#include <string>

// 個人: クラス記号_出席番号_氏_名_タイトル
// チーム: チームNo_タイトル
const char kWindowTitle[] = "LE2A_03_ウチダ_コウタ_MT4";

const float kWindowWidth = 1280.0f;
const float kWindowHeight = 720.0f;

static void DispVector2(const std::string& label, Vector2& vector) {

	ImGui::InputFloat2(label.c_str(), &vector.x, "%.3f", ImGuiInputTextFlags_ReadOnly);

}

static void DispFloat(const std::string& label, float& val) {

	ImGui::InputFloat(label.c_str(), &val,0.0f, 0.0f, "%.3f", ImGuiInputTextFlags_ReadOnly);

}

static Vector2 ToScreen(const Vector2& posWorld) {

	return { posWorld.x + 256.0f, -posWorld.y + 592.0f };

}

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<DeltaTime> timeManager = std::make_unique<DeltaTime>();
	float deltaTime = 0.0f;

	float bikeX = 0.0f;

	Vector2 position = { bikeX, ConstSlope::f(bikeX) };
	float slope = ConstSlope::fPrime(bikeX);
	Vector2 forward = VectorNormalize(Vector2{ 1.0f, slope });

	Vector2 slopeEnd = { 2.0f, ConstSlope::f(2.0f) };

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

		if (keys[DIK_A]) {
			bikeX -= kThirtySecond;
		}

		if (keys[DIK_D]) {
			bikeX += kThirtySecond;
		}

		bikeX = std::clamp(bikeX, 0.0f, 2.0f);

		position = { bikeX, ConstSlope::f(bikeX) };
		slope = ConstSlope::fPrime(bikeX);
		forward = VectorNormalize(Vector2{ 1.0f, slope });

		ImGui::Begin("slope");

		ImGui::Text("A, D: Move");

		DispVector2("position", position);

		DispVector2("forward", forward);

		DispFloat("slope(incline)", slope);

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///



		///
		/// ↑描画処理ここまで
		///

		Vector2 bikeFrontEndScreen = ToScreen(position * kPixelPerMetor + forward * 0.125f * kPixelPerMetor);

		Vector2 bikeBackEndScreen = ToScreen(position * kPixelPerMetor - forward * 0.125f * kPixelPerMetor);

		NoviceUtility::DrawLine(bikeBackEndScreen, bikeFrontEndScreen, RED);

		NoviceUtility::DrawCircle(bikeBackEndScreen, kPixelPerMetor * kThirtySecond, RED);

		NoviceUtility::DrawCircle(bikeFrontEndScreen, kPixelPerMetor * kThirtySecond, RED);

		Vector2 slopeEndScreen = ToScreen(slopeEnd);
		Vector2 slopeEndScreenBelow = ToScreen({ slopeEnd.x, 0.0f });
		Vector2 groundEndScreen[2] = { ToScreen({ 0.0f, 0.0f }), ToScreen({ 5.4f , 0.0f }) };

		NoviceUtility::DrawLine(slopeEndScreen, slopeEndScreenBelow, WHITE);

		NoviceUtility::DrawLine(groundEndScreen[0], groundEndScreen[1], WHITE);

		for (size_t i = 0; i < 16; ++i) {

			const float xPerTick = 2.0f / 16.0f;

			const float x0 = xPerTick * static_cast<float>(i);
			const float x1 = xPerTick * static_cast<float>(i + 1);

			Vector2 posInSlope[2] = { ToScreen(Vector2{ x0, ConstSlope::f(x0) } * kPixelPerMetor), ToScreen(Vector2{x1, ConstSlope::f(x1)}* kPixelPerMetor)};

			NoviceUtility::DrawLine(posInSlope[0], posInSlope[1], WHITE);

		}

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

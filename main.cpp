#include "AABB.h"
#include "Ball.h"
#include "Bezier.h"
#include "Camera.h"
#include "Clamp.h"
#include "Collision.h"
#include "DeltaTime.h"
#include "DrawShapes.h"
#include "Line.h"
#include "MathImGui.h"
#include "Matrix3D.h"
#include "Movement.h"
#include "MyImGui.h"
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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, static_cast<int>(kWindowWidth), static_cast<int>(kWindowHeight));

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	std::unique_ptr<DeltaTime> timeManager = std::make_unique<DeltaTime>();
	float deltaTime = 0.0f;

	float carT = 0.0f;

	Bezier2Vec2 bezier{};

	bezier.p[0] = {200.0f, 570.0f};
	bezier.p[1] = { 800.0f, 70.0f };
	bezier.p[2] = { 1080.0f, 570.0f };

	Vector2 carPos{};
	Vector2 carForward{};

	Vector2 adjustedForward{};

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



		ImGui::Begin("bezier");

		ImGui::Text("<drag>");

		ImGui::SliderFloat("t", &carT, 0.0f, 1.0f);
		
		ImGui::SliderFloat("p1 x", &bezier.p[1].x, 400.0f, 800.0f);
		ImGui::SliderFloat("p1 y", &bezier.p[1].y, 20.0f, 570.0f);

		carPos = Bezier(bezier, carT);
		carForward = VectorNormalize(BezierDeriative(bezier, carT));

		ImGui::Text("<display>");

		DispVector2("position", carPos);

		DispVector2("forward", carForward);

		adjustedForward = carForward * 120.0f;

		DispVector2("forward * 120.0f", adjustedForward);

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

		NoviceUtility::DrawLine(carPos, carPos + adjustedForward, RED);

		for (size_t i = 0; i < 16; ++i) {

			const float xPerTick = 1.0f / 16.0f;

			const float x0 = xPerTick * static_cast<float>(i);
			const float x1 = xPerTick * static_cast<float>(i + 1);

			Vector2 posInBezier[2] = { Bezier(bezier, x0), Bezier(bezier, x1) };

			NoviceUtility::DrawLine(posInBezier[0], posInBezier[1], WHITE);

		}

		NoviceUtility::DrawCircle(carPos, kPixelPerMetor * kThirtySecond, GREEN);

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

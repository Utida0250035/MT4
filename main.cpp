#include "DrawShapes.h"
#include "Matrix3D.h"
#include "Sphere.h"
#include <algorithm>
#include <cmath>
#include <Novice.h>
#include <numbers>
#include <ImGui.h>

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

	Vector3 cameraPosition{ 0.0f, 1.9f, -6.49f };

	Vector3 cameraRotate{ 0.26f, 0.0f, 0.0f };

	Sphere sphere{};

	sphere.center = {};
	sphere.radius = 1.0f;


	Vector3 scale{ 1.2f, 0.79f, -2.1f };
	Vector3 rotate{ 0.4f, 1.43f, -0.8f };
	Vector3 translate{2.7f, -4.15f, 1.57f};
	Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);


	translate = Vector3{4.1f, 2.6f, 0.8f};
	scale = Vector3{ 1.5f, 5.2f, 7.3f };
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Vector3 point{ 2.3f, 3.8f, 1.4f };
	Matrix4x4 transformMatrix = {
		1.0f, 2.0f, 3.0f, 4.0f,
		3.0f, 1.0f, 1.0f, 2.0f,
		1.0f, 4.0f, 2.0f, 3.0f,
		2.0f, 2.0f, 1.0f, 3.0f
	};
	Vector3 transformed = Transform(point, transformMatrix);

	Matrix4x4 m1 = {
		3.2f, 0.7f, 9.6f, 4.4f,
		5.5f, 1.3f, 7.8f, 2.1f,
		6.9f, 8.0f, 2.6f, 1.0f,
		0.5f, 7.2f, 5.1f, 3.3f
	};

	Matrix4x4 m2 = {
		4.1f, 6.5f, 3.3f, 2.2f,
		8.8f, 0.6f, 9.9f, 7.7f,
		1.1f, 5.5f, 6.6f, 0.0f,
		3.3f, 9.9f, 8.8f, 2.2f
	};

	Matrix4x4 resultAdd = Add(m1, m2);
	Matrix4x4 resultMultiply = Multiply(m1, m2);
	Matrix4x4 resultSubtract = Subtract(m1, m2);
	Matrix4x4 inverseM1 = Inverse(m1);
	Matrix4x4 inverseM2 = Inverse(m2);
	Matrix4x4 transposeM1 = Transpose(m1);
	Matrix4x4 transposeM2 = Transpose(m2);
	Matrix4x4 identity = MakeIdentity4x4();

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

		ImGui::Begin("debug");

		ImGui::DragFloat3("cameraTranslate", &cameraPosition.x, 0.0625f);

		ImGui::DragFloat3("cameraRotate", &cameraRotate.x, 0.0625f);

		ImGui::DragFloat3("sphereCenter", &sphere.center.x, 0.0625f);

		ImGui::DragFloat("sphereRadius", &sphere.radius, 0.0625f);

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Matrix4x4 cameraMatrix = MakeWorldMatrix(cameraPosition, Vector3{ 1.0f, 1.0f, 1.0f }, cameraRotate);

		Matrix4x4 viewMatrix = Inverse(cameraMatrix);

		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(0.45f, kWindowWidth / kWindowHeight, 0.1f, 100.0f);

		Matrix4x4 viewProjectionMatrix = viewMatrix * projectionMatrix;

		Matrix4x4 viewportMatrix = MakeViewportMatrix(0.0f, 0.0f, kWindowWidth, kWindowHeight, 0.0f, 1.0f);

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		DrawSphere(sphere, viewProjectionMatrix, viewportMatrix, 0x333333FF);


		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");


		MatrixScreenPrintf(300, 0, resultAdd, "Add");

		MatrixScreenPrintf(300, kMatrixPrintRowHeight * 5, resultSubtract, "Subtract");

		MatrixScreenPrintf(300, kMatrixPrintRowHeight * 5 * 2, resultMultiply, "Multiply");

		MatrixScreenPrintf(300, kMatrixPrintRowHeight * 5 * 3, inverseM1, "inverseM1");
		
		MatrixScreenPrintf(300, kMatrixPrintRowHeight * 5 * 4, inverseM2, "inverseM2");

		MatrixScreenPrintf(300 + kMatrixPrintColumnWidth * 5, 0, transposeM1, "transposeM1");

		MatrixScreenPrintf(300 + kMatrixPrintColumnWidth * 5, kMatrixPrintRowHeight * 5, transposeM2, "transposeM2");

		MatrixScreenPrintf(300 + kMatrixPrintColumnWidth * 5, kMatrixPrintRowHeight * 5 * 2, identity, "identity");


		VectorScreenPrintf(900, 0, transformed, "transformed");

		MatrixScreenPrintf(900, kMatrixPrintRowHeight * 5, translateMatrix, "translateMatrix");

		MatrixScreenPrintf(900, kMatrixPrintRowHeight * 5 * 2, scaleMatrix, "scaleMatrix");

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

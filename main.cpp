#include "Matrix3D.h"
#include <Novice.h>

// 個人: クラス記号_出席番号_氏_名_タイトル
// チーム: チームNo_タイトル
const char kWindowTitle[] = "LC1A_01_ウチダ_コウタ_MT3";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Vector3 v1{ 1.0f, 3.0f, -5.0f };
	Vector3 v2{ 4.0f, -1.0f, 2.0f };
	float k = 4.0f;

	Vector3 resultVecAdd = v1 + v2;

	Vector3 resultVecSubtract = v1 - v2;

	Vector3 resultVecMultiply = k * v1;

	float resultDot = VectorDot(v1, v2);

	float resultLength = VectorLength(v1);

	Vector3 resultNormalize = VectorNormalize(v2);

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

	Matrix4x4 resultMatAdd = m1 + m2;
	Matrix4x4 resultMatMultiply = m1 * m2;
	Matrix4x4 resultMatSubtract = m1 - m2;

	Matrix4x4 inverseM1 = MatrixInverse(m1);
	Matrix4x4 inverseM2 = MatrixInverse(m2);
	Matrix4x4 transposeM1 = MatrixTranspose(m1);
	Matrix4x4 transposeM2 = MatrixTranspose(m2);
	Matrix4x4 identityMat = MakeIdentityMatrix4x4();

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		/*MatrixScreenPrintf(0, 0, resultMatAdd, "Add");

		MatrixScreenPrintf(0, kMatrixPrintRowHeight * 5, resultMatSubtract, "Subtract");

		MatrixScreenPrintf(0, kMatrixPrintRowHeight * 5 * 2, resultMatMultiply, "Multiply");

		MatrixScreenPrintf(0, kMatrixPrintRowHeight * 5 * 3, inverseM1, "inverseM1");

		MatrixScreenPrintf(0, kMatrixPrintRowHeight * 5 * 4, inverseM2, "inverseM2");

		MatrixScreenPrintf(kMatrixPrintColumnWidth * 5, 0, transposeM1, "transposeM1");

		MatrixScreenPrintf(kMatrixPrintColumnWidth * 5, kMatrixPrintRowHeight * 5, transposeM2, "transposeM2");

		MatrixScreenPrintf(kMatrixPrintColumnWidth * 5, kMatrixPrintRowHeight * 5 * 2, identityMat, "identity");*/

		VectorScreenPrintf(640, 0, resultVecAdd, " : Add");
		VectorScreenPrintf(640, kVectorPrintRowHeight, resultVecSubtract, " : Subtract");
		VectorScreenPrintf(640, kVectorPrintRowHeight * 2, resultVecMultiply, " : Multiply");
		Novice::ScreenPrintf(640, kVectorPrintRowHeight * 3, "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(640, kVectorPrintRowHeight * 4, "%.02f : Length", resultLength);
		VectorScreenPrintf(640, kVectorPrintRowHeight * 5, resultNormalize, " : Normalize");

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

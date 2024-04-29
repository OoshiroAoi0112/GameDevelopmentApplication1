#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Scene/Scene.h"

//メイン関数
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//Windowモードで起動
	ChangeWindowMode(TRUE);

	//ウィンドウサイズ(横：640px、縦：480px)を設定
	SetGraphMode(640, 480, 32);

	//DxLibの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//ローカル変数定義
	Scene* scene = new Scene();    //シーン情報
	int result = 0;                //終了状態情報

	//描画先を裏画面から始めるように指定する
	SetDrawScreen(DX_SCREEN_BACK);

	try
	{
		//シーンの初期化
		scene->Initialize();

		//メインループ(ウィンドウの異常発生 or ESCAPEキーが押されたら、ループ終了)
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			//入力機能の更新
			InputControl::Update();

			//シーンの更新処理
			scene->Update();

			//画面の初期化
			ClearDrawScreen();

			//シーンの描画処理
			scene->Draw();

			//裏画面の内容を表画面に反映
			ScreenFlip();
		}
	}
	catch (const char* error_log)
	{
		//エラー情報をLog.txtに出力する
		OutputDebugString(error_log);
		//異常状態に更新する
		result = -1;
	}

	//シーン情報の削除をする
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}

	//DxLibの終了処理
	DxLib_End();

	//終了状態を通知
	return result;


}
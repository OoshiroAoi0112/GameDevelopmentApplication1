#pragma once
#define SCORE_DIGIT_MAX (5)//スコアの最大桁数

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

class Scene
{
private:
	std::vector<GameObject*>objects;
	int back_image;         //背景画像
	int timer_image;         //時計のマーク
	int s_str_image;        //スコア文字画像
	int hs_str_image;        //ハイスコア文字画像
	int number_image[11];         //数字0〜9

	int create_enemy[ENEMY_TYPE];    //敵の最大出現数配列
	int create_count;       //生成する敵のカウント

	int score;              //スコア
	int s_digit;            //スコアの桁数
	int score_image[SCORE_DIGIT_MAX];     //スコアを一桁ずつ格納、それに応じた画像の格納

	int result_image;       //スコアに応じた評価結果画像を格納
	int result_anim_count;  //ゲーム終了時にフィニッシュの画像から評価画像に切り替える間隔

	int limit_time;         //制限時間
	int time_count;         //フレームをカウントして60毎に制限時間を１減らす
	int t_digit;            //残り時間の桁数
	int time_image[2];      //残り時間を一桁ずつ格納、それに応じた画像の格納

	class Player* player;   //プレイヤーの情報を持った変数
public:

	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理  //引数const Vector2D& location
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();

		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//位置情報の設定
		new_object->SetLocation(location);
		//初期化処理
		new_object->Initialize();

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}

private:
	//スコアに値に合わせた画像を設定する
	void ScoreCal();

	//残り時間に合わせた画像を設定する
	void TimeCal();

	//引数に対応した数字画像を返却する
	int GetNumberImage(int number);

	//スコアの値に応じて表示するテキスト画像を変更する
	void Result();
};
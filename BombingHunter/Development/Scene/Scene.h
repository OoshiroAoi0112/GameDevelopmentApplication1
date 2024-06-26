#pragma once

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

	int create_enemy[4];    //敵の最大出現数配列
	int create_count;       //生成する敵のカウント

	int score;              //スコア
	int s_digit;            //スコアの桁数
	int score_image[5];     //スコアを一桁ずつ格納、それに応じた画像の格納

	int limit_time;         //制限時間
	int time_count;         //フレームをカウントして60毎に制限時間を１減らす
	int t_digit;            //残り時間の桁数
	int time_image[2];      //残り時間を一桁ずつ格納、それに応じた画像の格納

	class Player* player;
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
	void ScoreCal();

	void TimeCal();

	int GetNumberImage(int number);
};
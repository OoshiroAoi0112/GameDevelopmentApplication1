#pragma once
#include "../GameObject.h"
#define BLEND_MAX (255) //透過値最大値
#define IMAGE_MAX (5) //画像最大数

class Enemy :public GameObject
{
protected:
	Vector2D velocity;       //座標
	int animation[IMAGE_MAX];        //描画画像
	int animation_count;     //画像切り替えタイミング
	int flip_flag;           //画像の反転判定
	float init_enemy_y[5];   //エネミーの初期座標（ｙ）
	int blend;               //エネミーが徐々に透明になっていく値
	int give_score;          //

public:
	int score[ENEMY_TYPE];   //エネミーが消えるときにシーンに渡すスコアの値（種類別）
	bool s_drow;
	bool s_give;

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override;  //初期化
	virtual void Update() override;      //更新
	virtual void Draw() const override;  //描画
	virtual void Finalize() override;    //終了処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

	int GetGiveScore();

private:
	//移動処理
	void Movement();
protected:
	//アニメーション
	virtual void AnimeControl();
};



#pragma once
#include "../GameObject.h"

class Enemy :public GameObject
{
protected:
	Vector2D velocity;    //座標
	int animation[5];     //描画画像
	int animation_count;  //画像切り替えタイミング
	int flip_flag;        //画像の反転判定
	bool hit;             //動ける状態か（被弾したかどうか）
	float init_enemy_y[5];
	int blend;
	int score[ENEMY_TYPE];
	int give_score;

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



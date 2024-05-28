#pragma once
#include "../GameObject.h"

class Enemy :public GameObject
{
private:
	Vector2D velocity;
	int animation[2];
	int animation_count;
	int flip_flag;
	bool move_active;

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//移動処理
	void Movement();
	//アニメーション
	void AnimeControl();
};



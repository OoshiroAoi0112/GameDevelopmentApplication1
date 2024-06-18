#pragma once
#include "../Enemy.h"

class Hako :public Enemy
{
public:
	Hako();
	~Hako();

	virtual void Initialize();
	virtual void Update() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

};


#pragma once
#include "../Enemy.h"

class Hane :public Enemy
{
public:
	Hane();
	~Hane();

	virtual void Initialize() override;
	
	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

};

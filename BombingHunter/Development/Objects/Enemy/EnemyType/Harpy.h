#pragma once
#include "../Enemy.h"

class Harpy :public Enemy
{
public:
	Harpy();
	~Harpy();

	virtual void Initialize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

};
#pragma once
#include "../Enemy.h"

class Hako :public Enemy
{
public:
	Hako();
	~Hako();

	virtual void Initialize();

	//“–‚½‚è”»’è’Ê’mˆ—
	virtual void OnHitCollision(GameObject* hit_object) override;

};


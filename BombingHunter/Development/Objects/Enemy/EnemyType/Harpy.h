#pragma once
#include "../Enemy.h"

class Harpy :public Enemy
{
public:
	Harpy();
	~Harpy();

	virtual void Initialize() override;

	////“–‚½‚è”»’è’Ê’mˆ—
	//virtual void OnHitCollision(GameObject* hit_object) override;

};
#pragma once
#include "../Enemy.h"

class Hane :public Enemy
{
public:
	Hane();
	~Hane();

	virtual void Initialize() override;
	
	////“–‚½‚è”»’è’Ê’mˆ—
	//virtual void OnHitCollision(GameObject* hit_object) override;

};

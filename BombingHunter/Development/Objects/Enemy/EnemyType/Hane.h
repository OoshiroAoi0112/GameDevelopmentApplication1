#pragma once
#include "../Enemy.h"

class Hane :public Enemy
{
public:
	Hane();
	~Hane();

	virtual void Initialize() override;
	
	////�����蔻��ʒm����
	//virtual void OnHitCollision(GameObject* hit_object) override;

};

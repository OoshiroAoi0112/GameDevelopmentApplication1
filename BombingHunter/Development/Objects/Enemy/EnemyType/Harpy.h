#pragma once
#include "../Enemy.h"

class Harpy :public Enemy
{
public:
	Harpy();
	~Harpy();

	virtual void Initialize() override;

	////�����蔻��ʒm����
	//virtual void OnHitCollision(GameObject* hit_object) override;

};
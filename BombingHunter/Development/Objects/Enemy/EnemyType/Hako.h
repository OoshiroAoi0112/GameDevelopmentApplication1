#pragma once
#include "../Enemy.h"

class Hako :public Enemy
{
public:
	Hako();
	~Hako();

	virtual void Initialize();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

};


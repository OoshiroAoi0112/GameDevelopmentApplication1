#pragma once
#include "../Enemy.h"

class Gold :public Enemy
{
private:
	int animation[5];

public:
	Gold();
	~Gold();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();
	void AnimeControl();
};
#pragma once
#include "../Enemy.h"

class Harpy :public Enemy
{
private:
	int animation[2];

public:
	Harpy();
	~Harpy();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw()const override;
	virtual void Finalize() override;

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();
	void AnimeControl();
};
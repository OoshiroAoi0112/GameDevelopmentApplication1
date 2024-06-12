#pragma once
#include "../../GameObject.h"
#include "../../Utility/Vector2D.h"

class EnemyBullet : public GameObject
{
private:
	Vector2D velocity;
	int animation[4];
	int animation_count;
	bool anim_active;
	int image_count;

public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize() override;
	void Update() override;
	void Draw()const override;
	void Finalize() override;

	void OnHitCollision(GameObject* hit_object) override;

public:
	void Movement();
	void AnimeControl();
};


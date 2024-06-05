#pragma once
#include "../../GameObject.h"
#include "../../Utility/Vector2D.h"

class Bullet: public GameObject
{
private:
	int speed;
	int animation[4];
	int animation_count;
	bool anim_active;
	int image_count;

public:
	Bullet();
	~Bullet();

	void Initialize()override;
	void Update()override;
	void Draw()const override;
	void Finalize()override;

	void OnHitCollision(GameObject* hit_object)override;

public:
	void Movement();
	void AnimeControl();
	bool GetAnimActive()
	{
		return anim_active;
	}
};


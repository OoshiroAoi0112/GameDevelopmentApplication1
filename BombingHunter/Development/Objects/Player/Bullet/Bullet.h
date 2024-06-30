#pragma once
#include "../../GameObject.h"
#include "../../Utility/Vector2D.h"
#define IMAGE_MAX (4) //âÊëúç≈ëÂêî

class Bullet: public GameObject
{
private:
	Vector2D speed;
	int animation[IMAGE_MAX];
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
};


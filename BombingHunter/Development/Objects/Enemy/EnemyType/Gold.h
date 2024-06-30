#pragma once
#include "../Enemy.h"

class Gold :public Enemy
{
	int image_count;

public:
	Gold();
	~Gold();

	virtual void Initialize() override;

	//アニメーション制御（金の敵のみアニメーションが違う）
	virtual void AnimeControl() override;
};
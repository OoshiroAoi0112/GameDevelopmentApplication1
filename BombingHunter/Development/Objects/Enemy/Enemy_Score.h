#pragma once
#include "../../Objects/GameObject.h"

class Enemy_Score : public GameObject
{
private:
	int s_image[5];
	int number_image[11];
	int s_digit;
	int blend;

	Vector2D direction;

public:
	Enemy_Score();
	~Enemy_Score();

	virtual void Initialize() override;
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	void SetScoreImage(int score);

	int GetNumberImage(int number);
};


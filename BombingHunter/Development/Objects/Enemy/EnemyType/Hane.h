#pragma once
#include "../Enemy.h"

class Hane :public Enemy
{
public:
	Hane();
	~Hane();

	virtual void Initialize() override;
};

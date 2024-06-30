#pragma once
#include "../Enemy.h"

class Harpy :public Enemy
{
public:
	Harpy();
	~Harpy();

	virtual void Initialize() override;
};
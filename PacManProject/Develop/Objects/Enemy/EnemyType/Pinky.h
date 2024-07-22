#pragma once
#include "../EnemyBase.h"

class Pinky : public EnemyBase
{
public:
	//‰Šú‰»ˆ—
	void Initialize() override;

private:
	//’ÇÕƒ‚[ƒh
	void Tuiseki(float) override;
};


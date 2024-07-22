#pragma once
#include "../EnemyBase.h"

class Guzuta : public EnemyBase
{
public:
	//‰Šú‰»ˆ—
	void Initialize() override;

private:
	//’ÇÕƒ‚[ƒh
	void Tuiseki(float) override;
};


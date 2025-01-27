#pragma once
#include "../EnemyBase.h"

class Akabe : public EnemyBase
{
public:
	//‰Šú‰»ˆ—
	void Initialize() override;

	Akabe();
	~Akabe();

private:
	//’ÇÕƒ‚[ƒh
	void Tuiseki(float) override;
};


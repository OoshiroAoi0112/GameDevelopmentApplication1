#pragma once
#include "../EnemyBase.h"

class Pinky : public EnemyBase
{
public:
	//初期化処理
	void Initialize() override;

private:
	//追跡モード
	void Tuiseki(float) override;
};


#pragma once
#include "../EnemyBase.h"

class Guzuta : public EnemyBase
{
public:
	//����������
	void Initialize() override;

private:
	//�ǐՃ��[�h
	void Tuiseki(float) override;
};


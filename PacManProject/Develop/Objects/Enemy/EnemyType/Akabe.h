#pragma once
#include "../EnemyBase.h"

class Akabe : public EnemyBase
{
public:
	//����������
	void Initialize() override;

private:
	//�ǐՃ��[�h
	void Tuiseki(float) override;
};


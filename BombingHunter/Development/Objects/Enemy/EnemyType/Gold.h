#pragma once
#include "../Enemy.h"

class Gold :public Enemy
{
	int image_count;

public:
	Gold();
	~Gold();

	virtual void Initialize() override;

	//�A�j���[�V��������i���̓G�̂݃A�j���[�V�������Ⴄ�j
	virtual void AnimeControl() override;
};
#pragma once
#include "../Enemy.h"

class Gold :public Enemy
{
	int image_count;

public:
	Gold();
	~Gold();

	virtual void Initialize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	//�A�j���[�V��������i���̓G�̂݃A�j���[�V�������Ⴄ�j
	virtual void AnimeControl() override;
};
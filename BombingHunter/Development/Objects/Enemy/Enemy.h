#pragma once
#include "../GameObject.h"

class Enemy :public GameObject
{
protected:
	Vector2D velocity;    //���W
	int animation[5];     //�`��摜
	int animation_count;  //�摜�؂�ւ��^�C�~���O
	int flip_flag;        //�摜�̔��]����
	bool hit;             //�������Ԃ��i��e�������ǂ����j
	float init_enemy_y[5];
	int blend;
	int score[ENEMY_TYPE];
	int give_score;

public:
	Enemy();
	~Enemy();

	virtual void Initialize() override;  //������
	virtual void Update() override;      //�X�V
	virtual void Draw() const override;  //�`��
	virtual void Finalize() override;    //�I������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	int GetGiveScore();

private:
	//�ړ�����
	void Movement();
protected:
	//�A�j���[�V����
	virtual void AnimeControl();
};



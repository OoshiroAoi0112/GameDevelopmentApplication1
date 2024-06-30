#pragma once
#include "../GameObject.h"
#define BLEND_MAX (255) //���ߒl�ő�l
#define IMAGE_MAX (5) //�摜�ő吔

class Enemy :public GameObject
{
protected:
	Vector2D velocity;       //���W
	int animation[IMAGE_MAX];        //�`��摜
	int animation_count;     //�摜�؂�ւ��^�C�~���O
	int flip_flag;           //�摜�̔��]����
	float init_enemy_y[5];   //�G�l�~�[�̏������W�i���j
	int blend;               //�G�l�~�[�����X�ɓ����ɂȂ��Ă����l
	int give_score;          //

public:
	int score[ENEMY_TYPE];   //�G�l�~�[��������Ƃ��ɃV�[���ɓn���X�R�A�̒l�i��ޕʁj
	bool s_drow;
	bool s_give;

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



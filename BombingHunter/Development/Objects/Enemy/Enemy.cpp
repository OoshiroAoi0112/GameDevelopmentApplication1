#include "Enemy.h"
#include "EnemyType/Hako.h"
#include "EnemyType/Hane.h"
#include "EnemyType/Harpy.h"
#include "EnemyType/Gold.h"
#include "../../Utility/InputControl.h"
#include <math.h>
#include "DxLib.h"


//�R���X�g���N�^
Enemy::Enemy() :animation_count(0), flip_flag(FALSE),hit(false),blend(250), give_score(0)
{
	for (int i = 0; i < 5; i++)
	{
		animation[i] = NULL;               //�G�̉摜�i���G�̂�5���j
		init_enemy_y[i] = i * 50 + 180;    //�G���o������y���W
	}
	score[HAKO] = 200;
	score[HANE] = 30;
	score[HARPY] = -100;
	score[GOLD] = 1500;
}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{

}

//�X�V����
void Enemy::Update()
{
	//�����邩�ǂ���
	if (hit == false)
	{
		//�ړ�����
		Movement();
	}
	//�A�j���[�V��������
	AnimeControl();
}

//�`�揈��
void Enemy::Draw()const
{
	//��e�����Ȃ�
	if (hit == true)
	{
		//�`�惂�[�h���A���t�@�u�����h�ɂ���
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, blend);
	}
	//�G�l�~�[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);
	
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);

	//�f�o�b�O�p
#if _DEBUG
	//�ӂ蔻��̉���
	Vector2D box_collision_upper_left = location - box_size / 2.0f;
	Vector2D box_collision_lower_right = location + box_size / 2.0f;

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	int type = hit_object->GetObjectType();
	
	if (type == BULLET)
	{
		//��e�����瓮���Ȃ�����
		hit = true;
		animation_count = 0;
		box_size = 0.0f;
		give_score = score[create_type];
	}
}

//�ړ�����
void Enemy::Movement()
{
	//���݂̈���W�ɑ��������Z����
	location += velocity;

	//
	if (location.x > 640.0f || location.x < 0.0f)
	{
		//hit = true;
		destroy = true;
	}
}

//�A�j���[�V��������
void Enemy::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;
	if (hit == false)
	{
		//40�t���[���ڂɒB������
		if (animation_count >= 40)
		{
			//�J�E���g�̃��Z�b�g
			animation_count = 0;

			//�摜�̐؂�ւ�
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
			}
		}
	}
	else
	{
		if (animation_count % 8 == 0)
		{
			location.x += 10.0f;
		}
		else if (animation_count % 8 == 4)
		{
			location.x -= 10.0f;
		}
		location.y += 0.5f;
		blend = blend - 5;

		//�G�̍폜
		if (animation_count >= 80)
		{
			destroy = true;
		}
	}
}

int Enemy::GetGiveScore()
{
	return give_score;
}
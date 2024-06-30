#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Player/Bullet/Bullet.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/EnemyType/Hako.h"
#include "../Objects/Enemy/EnemyType/Hane.h"
#include "../Objects/Enemy/EnemyType/Harpy.h"
#include "../Objects/Enemy/EnemyType/Gold.h"
#include "../Objects/Enemy/Enemy_Score.h"
#include "../Objects/Enemy/Bullet/EnemyBullet.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include <math.h>

//�R���X�g���N�^
Scene::Scene() :
	objects(),
	create_count(0),
	score(0),
	s_digit(0),
	limit_time(0),
	time_count(0),
	t_digit(2)
{
	//�w�i�摜
	back_image = NULL;
	//�^�C�}�[�摜
	timer_image = NULL;
	//�X�R�A�����摜
	s_str_image = NULL;
	//�n�C�X�R�A�����摜
	hs_str_image = NULL;
	//�n�C�t�����܂߂������摜
	for (int i = 0; i < 10; i++)
	{
		number_image[i] = NULL;
	}

	//�G�̎�ނ��Ƃ̍ő吔
	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		create_enemy[i] = NULL;
	}
	player = NULL;

	//
	for (int i = 0; i < 5; i++)
	{
		score_image[i] = NULL;
	}
	time_image[0] = NULL;
	time_image[1] = NULL;
	for (int i = 0; i < 4; i++)
	{
		result_image[i] = NULL;
	}
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��X�q
	Finalize();
}

//����������
void Scene::Initialize()
{
	//�w�i�摜�ǂݍ���
	back_image = LoadGraph("Resource/Images/Stage/bg.png");
	//�^�C�}�[�摜
	timer_image = LoadGraph("Resource/Images/timer/timer.png");
	//�X�R�A�����摜
	s_str_image = LoadGraph("Resource/Images/score/score.png");
	//�n�C�X�R�A�����摜
	hs_str_image = LoadGraph("Resource/Images/score/hs.png");
	//�n�C�t���܂߂������摜
	number_image[0] = LoadGraph("Resource/Images/number/0.png");
	number_image[1] = LoadGraph("Resource/Images/number/1.png");
	number_image[2] = LoadGraph("Resource/Images/number/2.png");
	number_image[3] = LoadGraph("Resource/Images/number/3.png");
	number_image[4] = LoadGraph("Resource/Images/number/4.png");
	number_image[5] = LoadGraph("Resource/Images/number/5.png");
	number_image[6] = LoadGraph("Resource/Images/number/6.png");
	number_image[7] = LoadGraph("Resource/Images/number/7.png");
	number_image[8] = LoadGraph("Resource/Images/number/8.png");
	number_image[9] = LoadGraph("Resource/Images/number/9.png");
	number_image[10] = LoadGraph("Resource/Images/number/-.png");

	result_image[0] = LoadGraph("Resource/Images/result/BAD.png");
	result_image[1] = LoadGraph("Resource/Images/result/OK.png");
	result_image[2] = LoadGraph("Resource/Images/result/GOOD.png");
	result_image[3] = LoadGraph("Resource/Images/result/Perfect.png");
	
	//�G���[�`�F�b�N
	if (back_image == -1)
	{
		throw("�w�i�摜��������܂���");
	}
	if (timer_image == -1)
	{
		throw("�w�i�摜��������܂���");
	}
	if (s_str_image == -1)
	{
		throw("�w�i�摜��������܂���");
	}
	if (hs_str_image == -1)
	{
		throw("�w�i�摜��������܂���");
	}
	
	for (int i=0; i < 10; i++)
	{
		if (number_image[i] == -1)
		{
			throw("�w�i�摜��������܂���");
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (result_image[i] == -1)
		{
			throw("�]���摜��������܂���");
		}
	}

	//�G�̎�ނ��Ƃ̍ő�o����
	create_enemy[HAKO] = 3;
	create_enemy[HANE] = 3;
	create_enemy[HARPY] = 2;
	create_enemy[GOLD] = 1;

	//�v���C���[�𐶐�����
	player = CreateObject<Player>(Vector2D(320.0f, 50.0f));

	//�X�R�A�̏����摜"0"
	score_image[0] = number_image[0];

	//�������Ԃ̐ݒ�
	limit_time = 5;
	//�������Ԃ̏����摜"60"
	time_image[0] = number_image[0];
	
}

//�X�V����
void Scene::Update()
{
	if (limit_time > 0)
	{
		//�G�𐶐����邽�߂̃J�E���g
		create_count++;
		//1�b��1��ނ��G�𐶐�����
		if (create_count >= 60)
		{
			create_count = 0;
			//�G�̎�ޕ��������[�v����
			for (int i = 0; i < ENEMY_TYPE; i++)
			{
				//�G�̎�ނ��Ƃ̐����\����1�ȏ�ł��邩�ǂ���
				if (create_enemy[i] > 0)
				{
					if (i == HAKO)
					{
						CreateObject<Hako>(Vector2D(0.0f, 390.0f));
					}
					if (i == HANE)
					{
						CreateObject<Hane>(Vector2D(0.0f, 300.0f));
					}
					if (i == HARPY)
					{
						CreateObject<Harpy>(Vector2D(0.0f, 200.0f));
					}
					if (i == GOLD)
					{
						CreateObject<Gold>(Vector2D(0.0f, 400.0f));
					}
					//CreateObject<Enemy>(gene, i); 
					create_enemy[i] -= 1;
				}
			}
		}

		//F�������ƒe�𐶐�����
		if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			if (player->shot_flag == true)
			{
				CreateObject<Bullet>(Vector2D(objects[0]->GetLocation()));
				player->shot_flag = false;
			}
		}

		//���Ԋu�œG���e��ł�
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->GetObjectType() == ENEMY)
			{
				if (objects[i]->GetShotFlag() == true)
				{
					//�G�̒e�𐶐�
					EnemyBullet* obj = CreateObject<EnemyBullet>(Vector2D(objects[i]->GetLocation()));
					//���������e�̈ړ��ʌ���
					obj->SetDirection(player->GetLocation());
					//shotflag �� false �ɂ��Č��ĂȂ�����
					objects[i]->SetShotFlag();
				}
			}
		}

		//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
		for (GameObject* obj : objects)
		{
			if (obj->GetDestroy() == false)
			{
				obj->Update();
			}
		}

		//���Ԋu�œG���e��ł�
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->GetObjectType() == ENEMY)
			{
				if (objects[i]->GetHit() == true)
				{
					Vector2D loc = objects[i]->GetLocation();
					Enemy* e = dynamic_cast<Enemy*>(objects[i]);
					if (e->s_give == true)
					{
						score += e->GetGiveScore();
						if (score <= 0)
						{
							score = 0;
						}
						e->s_give = false;
					}
					if (e->s_drow == true)
					{
						Enemy_Score* es = CreateObject<Enemy_Score>(Vector2D(loc));
						es->SetScoreImage(e->GetGiveScore());
						e->s_drow = false;
					}
				}
			}
		}

		//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
		for (int i = 0; i < objects.size(); i++)
		{
			for (int j = i + 1; j < objects.size(); j++)
			{
				//�����蔻��`�F�b�N����
				HitCheckObject(objects[i], objects[j]);
			}
		}

		//�I�u�W�F�N�g�̍폜
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects[i]->GetDestroy())
			{
				if (objects[i]->GetCreateType() < ENEMY_TYPE)
				{
					int type = objects[i]->GetCreateType();
					create_enemy[type]++;
					/*Enemy* e=dynamic_cast<Enemy*>(objects[i]);
					score+=e->GetGiveScore();
					if (score <= 0)
					{
						score = 0;
					}*/
				}
				if (objects[i]->GetObjectType() == BULLET)
				{
					player->shot_flag = true;
				}
				objects.erase(objects.begin() + i--);
			}
		}
		//�������Ԃ̌v�Z�Ɖ摜�i�[
		TimeCal();
		//�X�R�A�̉摜�i�[
		ScoreCal();
	}
	else
	{
		
	}
}

//�`�揈��
void Scene::Draw()const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0, 0, 640, 480, back_image, FALSE);
	//�^�C�}�[�摜�̕`��
	DrawRotaGraphF(30, 460, 0.7, 0, timer_image, TRUE, TRUE);
	//�c�莞�Ԃ̉摜�`��
	for (int i = 0; i < t_digit; i++)
	{
		DrawRotaGraphF(i * 20 + 60, 460, 1.5, 0, time_image[i], TRUE, FALSE, FALSE);
	}

	//�X�R�A�����摜�̕`��
	DrawRotaGraphF(190, 460, 1.3, DX_PI_F, s_str_image, TRUE, TRUE, TRUE);
	//�X�R�A�̉摜�`��
	for (int i = 0; i < s_digit; i++)
	{
		DrawRotaGraphF(i * 20 + 240, 460, 1.5, 0, score_image[i], TRUE, FALSE, FALSE);
	}

	//�n�C�X�R�A�����摜�̕`��
	DrawRotaGraphF(400, 460, 1.3, DX_PI_F, hs_str_image, TRUE, TRUE, TRUE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		//���������摜���\���ɂ���
		if (obj->GetDestroy() == false)
		{
			obj->Draw();
		}
	}

	if (limit_time <= 0)
	{
		DrawRotaGraphF(320, 240, 0.7, 0, result_image[0], TRUE, FALSE, FALSE);
	}
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();
}

//�����蔻��`�F�b�N����
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;
	
	//�������傫�����傫���ꍇ���AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

//���݂̃X�R�A���ォ��ꌅ�Â擾���A���̐����ɑ΂���摜������B
void Scene::ScoreCal()
{
	if (score >= 10000)
	{
		s_digit = 5;
	}
	else if (score >= 1000)
	{
		s_digit = 4;
	}
	else if (score >= 100)
	{
		s_digit = 3;
	}
	else if (score >= 10)
	{
		s_digit = 2;
	}
	else
	{
		s_digit = 1;
	}

	int s = score;
	for (int i = 0; i < 5; i++)
	{
		if (i < s_digit)
		{
			int p = pow(10, s_digit-(i+1));
			int image= s / p;
			score_image[i] = GetNumberImage(image);
			s = s % p;
		}
		else
		{
			score_image[i] = NULL;
		}
	}
}

void Scene::TimeCal()
{
	time_count++;
	if (time_count >= 60)
	{
		time_count = 0;
		limit_time--;
		if (limit_time <= 0)
		{
			limit_time = 0;
		}
	}

	if (limit_time >= 10)
	{
		t_digit = 2;
	}
	else
	{
		t_digit = 1;
	}

	int t = limit_time;
	for (int i = 0; i < t_digit; i++)
	{
		if (i < t_digit)
		{
			int p = pow(10, t_digit - (i + 1));
			int image = t / p;
			time_image[i] = GetNumberImage(image);
			t = t % p;
		}
		else
		{
			time_image[i] = NULL;
		}
	}
}

//�l�ɉ����������̉摜��Ԃ�
int Scene::GetNumberImage(int number)
{
	return number_image[number];
}

void Scene::Result()
{
	
}
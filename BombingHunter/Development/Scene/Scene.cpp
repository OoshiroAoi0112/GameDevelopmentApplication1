#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Player/Bullet/Bullet.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/EnemyType/Hako.h"
#include "../Objects/Enemy/EnemyType/Hane.h"
#include "../Objects/Enemy/EnemyType/Harpy.h"
#include "../Objects/Enemy/EnemyType/Gold.h"
#include "../Objects/Enemy/Bullet/EnemyBullet.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Scene::Scene() :objects(),create_count(0),score(0),s_digit(0)
{
	//�w�i�摜
	back_image = NULL;
	//�^�C�}�[�摜
	time_image = NULL;
	//�X�R�A�����摜
	s_str_image = NULL;
	//�n�C�X�R�A�����摜
	hs_str_image = NULL;
	//�n�C�t�����܂߂������摜
	for (int i = 0; i < 10; i++)
	{
		number[i] = NULL;
	}

	//�G�̎�ނ��Ƃ̍ő吔
	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		create_enemy[i] = NULL;
	}
	player = NULL;
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
	time_image = LoadGraph("Resource/Images/timer/timer.png");
	//�X�R�A�����摜
	s_str_image = LoadGraph("Resource/Images/score/score.png");
	//�n�C�X�R�A�����摜
	hs_str_image = LoadGraph("Resource/Images/score/hs.png");
	//�n�C�t���܂߂������摜
	number[0] = LoadGraph("Resource/Images/number/0.png");
	number[1] = LoadGraph("Resource/Images/number/1.png");
	number[2] = LoadGraph("Resource/Images/number/2.png");
	number[3] = LoadGraph("Resource/Images/number/3.png");
	number[4] = LoadGraph("Resource/Images/number/4.png");
	number[5] = LoadGraph("Resource/Images/number/5.png");
	number[6] = LoadGraph("Resource/Images/number/6.png");
	number[7] = LoadGraph("Resource/Images/number/7.png");
	number[8] = LoadGraph("Resource/Images/number/8.png");
	number[9] = LoadGraph("Resource/Images/number/9.png");
	number[10] = LoadGraph("Resource/Images/number/-.png");
	
	
	if (back_image == -1)
	{
		throw("�w�i�摜��������܂���");
	}
	if (time_image == -1)
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
		if (number[i] == -1)
		{
			throw("�w�i�摜��������܂���");
		}
	}

	create_enemy[HAKO] = 3;
	create_enemy[HANE] = 3;
	create_enemy[HARPY] = 2;
	create_enemy[GOLD] = 1;

	//�v���C���[�𐶐�����
	player = CreateObject<Player>(Vector2D(320.0f, 50.0f));
}

//�X�V����
void Scene::Update()
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
					CreateObject<Hako>(Vector2D(0.0f,390.0f));
				}
				if (i == HANE)
				{
					CreateObject<Hane>(Vector2D(0.0f,300.0f));
				}
				if (i == HARPY)
				{
					CreateObject<Harpy>(Vector2D(0.0f,200.0f));
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
	if (InputControl::GetKeyDown(KEY_INPUT_F))
	{
		CreateObject<Bullet>(Vector2D(objects[0]->GetLocation()));
	}

	//���Ԋu�œG���e��ł�
	for (int i=0;i<objects.size();i++)
	{
		if(objects[i]->GetObjectType() == ENEMY)
		{
			if (objects[i]->GetShotFlag() == true)
			{
				EnemyBullet* obj = CreateObject<EnemyBullet>(Vector2D(objects[i]->GetLocation()));
				obj->SetDirection(player->GetLocation());
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

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i+1; j < objects.size(); j++)
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
				Enemy* e=dynamic_cast<Enemy*>(objects[i]);
				score+=e->GetGiveScore();
			}
			objects.erase(objects.begin() + i--);
		}
	}
}

//�`�揈��
void Scene::Draw()const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0, 0, 640, 480, back_image, FALSE);
	//�^�C�}�[�摜�̕`��
	DrawRotaGraphF(30, 460, 0.7, 0, time_image, TRUE, TRUE);
	//�X�R�A�����摜�̕`��
	DrawRotaGraphF(190, 460, 1.3, DX_PI_F, s_str_image, TRUE, TRUE, TRUE);

	DrawFormatString(220, 460, GetColor(255, 255, 255), "%d", score);
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


void Scene::ScoreCal()
{
	if (score >= 10000)
	{
		s_digit = 4;
		
	}
}
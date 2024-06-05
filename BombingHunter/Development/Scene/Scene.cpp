#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Player/Bullet/Bullet.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Scene::Scene() :objects(),create_count(0)
{
	back_image = NULL;
	destroy_number = 0;
	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		create_enemy[i] = NULL;
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
	
	if (back_image == -1)
	{
		throw("�w�i�摜��������܂���");
	}

	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		switch (i)
		{
		case HAKO:
		case HANE:
			create_enemy[i] = 3;
			break;
		case HARPY:
			create_enemy[i] = 2;
			break;
		case GOLD:
			create_enemy[i] = 1;
			break;
		}
	}

	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(100.0f,100.0f),5);
	////�G�𐶐�����
	//CreateObject<Enemy>(Vector2D(400.0f,300.0f));
}

//�X�V����
void Scene::Update()
{
	create_count++;
	if (create_count >= 60)
	{
		create_count = 0;
		for (int i = 0; i < ENEMY_TYPE; i++)
		{
			if (create_enemy[i] > 0)
			{
				switch (i)
				{
					case 0:
						CreateObject<Enemy>(Vector2D(40.0f, 420.0f),i);
						create_enemy[i] -= 1;
						break;
					case 1:
						CreateObject<Enemy>(Vector2D(40.0f, 300.0f),i);
						create_enemy[i] -= 1;
						break;
					case 2:
						CreateObject<Enemy>(Vector2D(40.0f, 200.0f),i);
						create_enemy[i] -= 1;
						break;
					case 3:
						CreateObject<Enemy>(Vector2D(40.0f, 100.0f),i);
						create_enemy[i] -= 1;
						break;
				}
				
			}
		}
	}

	//F�������ƒe�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_F))
	{
		CreateBullet<Bullet>(Vector2D(objects[0]->GetLocation()));
	}

	//�V�[���ɑ��݂���I�u�W�F�N�g�̍X�V����
	for (GameObject* obj : objects)
	{
		if (obj->GetDestroy() == false)
		{
			obj->Update();
		}
	}
	//�e�̍X�V
	destroy_number = 0;
	for (GameObject* bullet : p_bullet)
	{
		if (bullet->GetDestroy() == false)
		{
			bullet->Update();
		}
		destroy_number++;
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 1; i < objects.size(); i++)
	{
		//�����蔻��`�F�b�N����
		HitCheckObject(objects[0], objects[i]);
	}

	//�e�ƓG���m�̓����蔻��`�F�b�N
	for (GameObject* obj : objects)
	{
		//�G����x���e�ɐG��Ă��Ȃ����
		if (!obj->GetHit())
		{
			for (int i = 0; i < p_bullet.size(); i++)
			{
				HitCheckObject(p_bullet[i], obj);
			}
		}
	}

	destroy_number = 0;
	for (GameObject* obj : objects)
	{
		if (obj->GetDestroy())
		{
			create_enemy[obj->GetObjectType()]++;
			objects.erase(objects.begin() + destroy_number);
			destroy_number--;
		}
		destroy_number++;
	}
	destroy_number = 0;
	for (GameObject* bullet : p_bullet)
	{
		if (bullet->GetDestroy())
		{
			p_bullet.erase(p_bullet.begin() + destroy_number);
			destroy_number--;
		}
		destroy_number++;
	}
	destroy_number = 0;
}

//�`�揈��
void Scene::Draw()const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0, 0, 640, 520, back_image, FALSE);

	//�V�[���ɑ��݂���I�u�W�F�N�g�̕`�揈��
	for (GameObject* obj : objects)
	{
		//���������摜���\���ɂ���
		if (obj->GetDestroy() == false)
		{
			obj->Draw();
		}
	}

	//��ʂɑ��݂���e�̕`��
	for (GameObject* bullet : p_bullet)
	{
		//���������摜���\���ɂ���
		if (bullet->GetDestroy() == false)
		{
			bullet->Draw();
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
	if (p_bullet.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}
	for (GameObject* bullet : p_bullet)
	{
		bullet->Finalize();
		delete bullet;
	}

	//���I�z��̉��
	objects.clear();

	p_bullet.clear();
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
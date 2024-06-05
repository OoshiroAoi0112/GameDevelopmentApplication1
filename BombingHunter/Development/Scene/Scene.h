#pragma once

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

class Scene
{
private:
	std::vector<GameObject*>objects;
	std::vector<GameObject*>p_bullet;
	int back_image;
	int create_enemy[4];
	int create_count;
	int destroy_number;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();

private:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);

	//�I�u�W�F�N�g��������  //����const Vector2D& location
	template<class T>
	T* CreateObject(const Vector2D& location,int object_type)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();

		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//
		new_object->SetObjectType(object_type);
		//����������
		new_object->Initialize();
		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}

	template<class B>
	B* CreateBullet(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		B* new_instance = new B();

		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("�Q�[���I�u�W�F�N�g�������ł��܂���ł���");
		}

		//����������
		new_object->Initialize();
		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		p_bullet.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};


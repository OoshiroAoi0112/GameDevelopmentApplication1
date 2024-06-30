#pragma once
#define SCORE_DIGIT_MAX (5)//�X�R�A�̍ő包��

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

class Scene
{
private:
	std::vector<GameObject*>objects;
	int back_image;         //�w�i�摜
	int timer_image;         //���v�̃}�[�N
	int s_str_image;        //�X�R�A�����摜
	int hs_str_image;        //�n�C�X�R�A�����摜
	int number_image[11];         //����0�`9

	int create_enemy[ENEMY_TYPE];    //�G�̍ő�o�����z��
	int create_count;       //��������G�̃J�E���g

	int score;              //�X�R�A
	int s_digit;            //�X�R�A�̌���
	int score_image[SCORE_DIGIT_MAX];     //�X�R�A���ꌅ���i�[�A����ɉ������摜�̊i�[

	int result_image;       //�X�R�A�ɉ������]�����ʉ摜���i�[
	int result_anim_count;  //�Q�[���I�����Ƀt�B�j�b�V���̉摜����]���摜�ɐ؂�ւ���Ԋu

	int limit_time;         //��������
	int time_count;         //�t���[�����J�E���g����60���ɐ������Ԃ��P���炷
	int t_digit;            //�c�莞�Ԃ̌���
	int time_image[2];      //�c�莞�Ԃ��ꌅ���i�[�A����ɉ������摜�̊i�[

	class Player* player;   //�v���C���[�̏����������ϐ�
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
	T* CreateObject(const Vector2D& location)
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

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);
		//����������
		new_object->Initialize();

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}

private:
	//�X�R�A�ɒl�ɍ��킹���摜��ݒ肷��
	void ScoreCal();

	//�c�莞�Ԃɍ��킹���摜��ݒ肷��
	void TimeCal();

	//�����ɑΉ����������摜��ԋp����
	int GetNumberImage(int number);

	//�X�R�A�̒l�ɉ����ĕ\������e�L�X�g�摜��ύX����
	void Result();
};
#include "Hako.h"
#include "DxLib.h"

//�R���X�g���N�^
Hako::Hako()
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
}

//�f�X�g���N�^
Hako::~Hako()
{

}

//����������
void Hako::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Enemy/hako/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/hako/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�G�̉摜������܂���\n");
	}

	//�ړ���
	velocity.x = GetRand(1) + 2;

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�e�ɓ����������ǂ���
	hit = false;

	//�����������ǂ���
	destroy = false;

	flip_flag = FALSE;
}

//�����蔻��ʒm����
void Hako::OnHitCollision(GameObject* hit_object)
{

}

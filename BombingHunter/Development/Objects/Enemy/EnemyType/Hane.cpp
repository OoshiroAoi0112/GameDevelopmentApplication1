#include "Hane.h"
#include "DxLib.h"

//�R���X�g���N�^
Hane::Hane()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Hane::~Hane()
{

}

//����������
void Hane::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Enemy/hane/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/hane/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�G�̉摜������܂���\n");
	}

	//�ړ���
	velocity.x = GetRand(4) + 1;

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
}


//�����蔻��ʒm����
void Hane::OnHitCollision(GameObject* hit_object)
{

}


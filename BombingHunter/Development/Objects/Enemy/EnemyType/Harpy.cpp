#include "harpy.h"
#include "DxLib.h"

//�R���X�g���N�^
Harpy::Harpy()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Harpy::~Harpy()
{

}

//����������
void Harpy::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Enemy/harpy/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/harpy/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�G�̉摜������܂���\n");
	}

	////0��1�������_���Ŏ��
	//�o������x���W�E�ړ���������E�摜�̌��������߂�
	int rand_loc = GetRand(1);
	int vec = GetRand(1) + 1;

	if (rand_loc == 0)
	{
		location.x = 0.0f;
		velocity.x = vec;
		flip_flag = FALSE;
	}
	else
	{
		location.x = 640.0f;
		velocity.x = -vec;
		flip_flag = TRUE;
	}

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

	object_type = ENEMY;

	create_type = HARPY;
}

//�����蔻��ʒm����
void Harpy::OnHitCollision(GameObject* hit_object)
{
	hit = true;
}

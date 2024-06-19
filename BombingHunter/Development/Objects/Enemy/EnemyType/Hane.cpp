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


	////0��1�������_���Ŏ��
	//�o������x���W�E�ړ���������E�摜�̌��������߂�
	int rand_loc = GetRand(1);
	int vec = GetRand(4) + 1;

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
	rand_loc = GetRand(3);
	location.y = init_enemy_y[rand_loc];

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 52.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�e�ɓ����������ǂ���
	hit = false;

	//�����������ǂ���
	destroy = false;

	//�I�u�W�F�N�g�̎��
	object_type = ENEMY;

	//�����������G�̔ԍ��i���O�j
	create_type = HANE;
}


////�����蔻��ʒm����
//void Hane::OnHitCollision(GameObject* hit_object)
//{
//	//hit = true;
//	__super::Enemy::OnHitCollision(hit_object);
//}


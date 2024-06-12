#include "Gold.h"
#include "DxLib.h"

//�R���X�g���N�^
Gold::Gold()
{
	image_count = 0;

	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
}

//�f�X�g���N�^
Gold::~Gold()
{

}

//����������
void Gold::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Enemy/gold/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/gold/2.png");
	animation[2] = LoadGraph("Resource/Images/Enemy/gold/3.png");
	animation[3] = LoadGraph("Resource/Images/Enemy/gold/4.png");
	animation[4] = LoadGraph("Resource/Images/Enemy/gold/5.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�G�̉摜������܂���\n");
	}

	////0��1�������_���Ŏ��
	//�o������x���W�E�ړ���������E�摜�̌��������߂�
	int rand_loc = GetRand(1);

	if (rand_loc == 0)
	{
		location.x = 0;
		velocity.x = 4;
		flip_flag = FALSE;
	}
	else
	{
		location.x = 640;
		velocity.x = -4;
		flip_flag = TRUE;
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 24.0f;

	//�����摜�̐ݒ�
	image = animation[3];

	//�e�ɓ����������ǂ���
	hit = false;

	//�����������ǂ���
	destroy = false;

	object_type = ENEMY;

	create_type = GOLD;
}

//�����蔻��ʒm����
void Gold::OnHitCollision(GameObject* hit_object)
{
	hit = true;
}


void Gold::AnimeControl()
{
	//�t���[���J�E���g�̉��Z
	animation_count++;
	if (hit == false)
	{
		//20�t���[�����Ƃɉ摜�̐؂�ւ�
		if (animation_count >= 20)
		{
			//�t���[���J�E���g�̃��Z�b�g
			animation_count = 0;
			//�ǂݍ��݂����摜�z��̈ʒu�����Z
			image_count++;
			//�摜�z��̖�����ǂݍ���ł���ꍇ��ԍŏ��ɖ߂�
			if (image == animation[4])
			{
				image = animation[0];
				image_count = 0;
			}
			else
			{
				image = animation[image_count];
			}
		}
	}
	//�˂ʉ��o
	else
	{
		if (animation_count % 8 == 0)
		{
			location.x += 5.0f;
		}
		else if (animation_count % 8 == 4)
		{
			location.x -= 5.0f;
		}
		location.y += 0.5f;
		//�G�̍폜
		if (animation_count >= 90)
		{
			destroy = true;

		}
	}
}
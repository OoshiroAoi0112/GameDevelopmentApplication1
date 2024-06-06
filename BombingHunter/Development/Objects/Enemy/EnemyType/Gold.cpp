#include "Gold.h"
#include "DxLib.h"

//�R���X�g���N�^
Gold::Gold()
{
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

	//�ړ���
	velocity.x = GetRand(1) + 2;

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[3];

	//�e�ɓ����������ǂ���
	hit = false;

	//�����������ǂ���
	destroy = false;
}

//�X�V����
void Gold::Update()
{

}

//�`�揈��
void Gold::Draw() const
{

}

//�I��������
void Gold::Finalize()
{

}

//�����蔻��ʒm����
void Gold::OnHitCollision(GameObject* hit_object)
{

}

//�ړ�����
void Gold::Movement()
{

}

//�A�j���[�V��������
void Gold::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;
	if (hit == false)
	{
		//40�t���[���ڂɒB������
		if (animation_count >= 40)
		{
			//�J�E���g�̃��Z�b�g
			animation_count = 0;

			//�摜�̐؂�ւ�
			if (image == animation[3])
			{
				image = animation[4];
			}
			else
			{
				image = animation[3];
			}
		}
	}
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
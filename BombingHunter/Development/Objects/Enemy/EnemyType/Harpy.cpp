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
}

//�X�V����
void Harpy::Update()
{

}

//�`�揈��
void Harpy::Draw() const
{

}

//�I��������
void Harpy::Finalize()
{

}

//�����蔻��ʒm����
void Harpy::OnHitCollision(GameObject* hit_object)
{

}

//�ړ�����
void Harpy::Movement()
{

}

//�A�j���[�V��������
void Harpy::AnimeControl()
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
			if (image == animation[0])
			{
				image = animation[1];
			}
			else
			{
				image = animation[0];
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
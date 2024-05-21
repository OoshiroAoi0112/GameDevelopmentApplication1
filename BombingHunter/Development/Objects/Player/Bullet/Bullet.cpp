#include "Bullet.h"
#include "DxLib.h"

//�R���X�g���N�^
Bullet::Bullet() :speed(4),animation_count(0),anim_active(0),image_count(0)
{
	for (int i=0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//�f�X�g���N�^
Bullet::~Bullet()
{

}

//����������
void Bullet::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Player/P_Bullet/bom.png");
	animation[1] = LoadGraph("Resource/Images/Player/P_Bullet/1.png");
	animation[2] = LoadGraph("Resource/Images/Player/P_Bullet/2.png");
	animation[3] = LoadGraph("Resource/Images/Player/P_Bullet/3.png");

	//�G���[�`�F�b�N
	for (int i=0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("�v���C���[�̒e�摜������܂���");
		}
	}
	//�����̐ݒ�
	radian =DX_PI_F/2;
	//�傫���̐ݒ�
	box_size = 32.0f;
	//�����摜�̐ݒ�
	image = animation[image_count];
}

//�X�V����
void Bullet::Update()
{
	if (destroy == false)
	{
		Movement();
	}
	if (image_count <= 3 && anim_active==1)
	{
		AnimeControl();
	}
}

//�`�揈��
void Bullet::Draw()const
{
	DrawRotaGraph(location.x, location.y, 0.7, radian,image, TRUE, FALSE);

#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Bullet::Finalize()
{
	//�g�p�����摜���������
	for (int i=0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//�����蔻��ʒm����
void Bullet::OnHitCollision(GameObject* hit_object)
{
	//���������Ƃ��̏���
	speed = 0;
	radian = 0;
	image_count = 1;
	anim_active = 1;
	destroy = true;
}

//�ړ�����
void Bullet::Movement()
{
	location.y += speed;
	if (location.y >= 420)
	{
		speed = 0;
		radian = 0;
		image_count = 1;
		anim_active = 1;
	}
}

void Bullet::AnimeControl()
{
	animation_count++;
	if (animation_count >= 30)
	{
		image_count++;
		switch (image_count)
		{
		case 0:
		case 1:
			break;
		case 2:
			destroy = true;
			break;
		case 3:
			anim_active = 0;
			break;
		}
		animation_count = 0;
	}
	image = animation[image_count];
}
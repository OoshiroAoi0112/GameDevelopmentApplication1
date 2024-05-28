#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() :animation_count(0), flip_flag(FALSE),move_active(true)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{

	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Enemy/hako/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/hako/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("�n�R�G�̉摜������܂���\n");
	}
	//�ړ���
	velocity.x = 2;

	//�����̐ݒ�
	radian = 0.0;

	//�傫���̐ݒ�
	scale = 64.0;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����������ǂ���
	destroy = false;
}

//�X�V����
void Enemy::Update()
{
	//�����邩�ǂ���
	if (move_active == true)
	{
		//�ړ�����
		Movement();
	}
	//�A�j���[�V��������
	AnimeControl();
}

//�`�揈��
void Enemy::Draw()const
{
	//��e�����Ȃ�
	if (move_active == false)
	{
		//�`�惂�[�h���A���t�@�u�����h�ɂ���
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);
	}
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);

	//�f�o�b�O�p
#if _DEBUG
	//�ӂ蔻��̉���
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale / 2.0f);
	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) *
		(float)scale / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//��e�����瓮���Ȃ�����
	move_active = false;
	animation_count = 0;
}

//�ړ�����
void Enemy::Movement()
{
	//�n�R�G�̍����ݒ�
	location.y = 480.0f-scale;

	//���݂̈���W�ɑ��������Z����
	location += velocity;

	//�E�̕ǂɓ�����ƍ��̕ǂ���o�Ă���
	if (location.x > 640.0f)
	{
		velocity.x *= -1;
			flip_flag = TRUE;
	}
	if (location.x < 0.0f)
	{
		velocity.x *= -1;
		flip_flag = FALSE;
	}
}

//�A�j���[�V��������
void Enemy::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;
	if (move_active == true)
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
		location.y -= 1.0f;
		//�G�̍폜
		if (animation_count >= 90)
		{
			destroy = true;
			Finalize();
		}
	}
}

#include "Player.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Player::Player() :animation_count(0), flip_flag(FALSE),shot_flag(true)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//�f�X�g���N�^
Player::~Player()
{

}

//����������
void Player::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Player/���1.png");
	animation[1] = LoadGraph("Resource/Images/Player/���2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("���p�C���b�g�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�傫���̐ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�������Ă��邩�ǂ���
	hit = false;

	//�����������ǂ���
	destroy = false;

	//�I�u�W�F�N�g�̎��
	object_type = PLAYER;
}

//�X�V����
void Player::Update()
{
	//�ړ�����
	Action();
	//�A�j���[�V��������
	AnimeControl();
}

//�`�揈��
void Player::Draw()const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);
	
	//�f�o�b�O�p
#if _DEBUG
	//�ӂ蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//�I��������
void Player::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Player::OnHitCollision(GameObject* hit_object)
{
	//���������Ƃ��̏���

}

//�v���C���[���쏈��
void Player::Action()
{
	//�ړ�����
	//�ړ��̑���
	Vector2D velocity = 0.0f;

	//���E�ړ�
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -5.0f;
		flip_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 5.0f;
		flip_flag = FALSE;
	}
	else
	{
		velocity.x += 0.0f;
	}

	//��ʒ[����o�Ȃ��悤�ɂ���
	if (location.x+velocity.x<0 + box_size.x / 2 || location.x+velocity.x>640-box_size.x / 2)
	{
		velocity.x = 0;
	}

	//���݂̈���W�ɑ��������Z����
	location += velocity;
}

//�A�j���[�V��������
void Player::AnimeControl()
{
	//�t���[���J�E���g�����Z����
	animation_count++;

	//60�t���[���ڂɒB������
	if (animation_count >= 60)
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

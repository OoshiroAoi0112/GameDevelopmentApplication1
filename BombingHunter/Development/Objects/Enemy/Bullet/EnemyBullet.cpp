#include "EnemyBullet.h"
#include "math.h"
#include "DxLib.h"

//�R���X�g���N�^
EnemyBullet::EnemyBullet() :
	velocity(0.0f),
	animation_count(0),
	anim_active(false),
	image_count(0)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//�f�X�g���N�^
EnemyBullet::~EnemyBullet()
{

}

//����������
void EnemyBullet::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/Enemy/E_Bullet/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/E_Bullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images/Enemy/E_Bullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images/Enemy/E_Bullet/eff3.png");

	//�G���[�`�F�b�N
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("�G�̒e�摜���Ȃ���");
		}
	}
	

	//�����̐ݒ�
	radian = 0;
	//�傫���̔w���
	box_size = 20.0f;
	//�����摜�̐ݒ�
	image = animation[image_count];  //animation[0]
	//�I�u�W�F�N�g�̎��
	object_type = ENEMY_BULLET;
}

//�X�V����
void EnemyBullet::Update()
{
	//�q�b�g��Ԃ���Ȃ��Ȃ�Ȃ�ړ����āA�q�b�g�����Ȃ甚���̃A�j���[�V�������s��
	if (hit == false)
	{
		Movement();
	}
	if (image_count <= 4 && anim_active == true)
	{
		AnimeControl();
	}
}

//�`�揈��
void EnemyBullet::Draw() const
{
	DrawRotaGraph(location.x, location.y, 0.7, radian, image, TRUE, FALSE);

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
void EnemyBullet::Finalize()
{
	//�g�p�����摜�����
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//�����蔻��ʒm����
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//�I�u�W�F�N�g�̎�ނ��擾���Ă���ɉ����ē����蔻����s�������߂�
	int type=hit_object->GetObjectType();

	if (type == PLAYER)
	{
		velocity = 0.0f;
		image_count = 1;
		anim_active = true;
		hit = true;
		box_size = 0.0f;
	}
}

//�ړ�����
void EnemyBullet::Movement()
{
	location += velocity;
	if (location.x < 0.0f || location.x>640.0f || location.y < 0.0f)
	{
		velocity = 0.0f;
		destroy = true;
	}
}

//�A�j���[�V��������
void EnemyBullet::AnimeControl()
{
	animation_count++;
	if (animation_count >= 15)
	{
		image_count++;
		switch (image_count)
		{
		case 0:
		case 2:
			break;
		case 1:
			hit = true;
			break;
		case 3:
			anim_active = false;
			destroy = true;
			break;
		}
		animation_count = 0;
	}
	if (image_count <= 3)
	{
		image = animation[image_count];
	}
}

void EnemyBullet::SetDirection(const Vector2D& dir)
{
	Vector2D vec;
	vec.x = (-(location.x - dir.x)) / (60.0f + (location.y / 10));
	velocity.x = vec.x;

	vec.y = (-(location.y - dir.y))/ (60.0f + (location.x / 10));
	velocity.y = vec.y;
}

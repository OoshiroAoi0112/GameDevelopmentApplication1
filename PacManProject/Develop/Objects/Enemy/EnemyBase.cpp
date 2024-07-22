#include "EnemyBase.h"
#include "DxLib.h"

//�R���X�g���N�^
EnemyBase::EnemyBase() :
	nawabari_loc(0.0f),
	state(WAIT),
	speed(5),
	player(nullptr),
	spawn_loc(0.0f),
	move_animation(),
	eye_animation(),
	flash_count(0),
	gate(false),
	mode_time(0.0f),
	anim_count(0.0f)
{
}

//�f�X�g���N�^
EnemyBase::~EnemyBase()
{
}

//����������
void EnemyBase::Initialize()
{

}

//�X�V����
void EnemyBase::Update(float delta_second)
{

}

//Hit����
void EnemyBase::OnHitCollision(GameObjectBase*)
{

}

//�`�揈��
void EnemyBase::Draw(const Vector2D&)const
{

}

//�I������
void EnemyBase::Finalize()
{

}

//�ړ�����
void EnemyBase::Movement(float delta_second)
{

}

//�ǐՃ��[�h
void EnemyBase::Tuiseki(float delta_second)
{

}

//�꒣�胂�[�h
void EnemyBase::Nawabari(float delta_second)
{

}

//���������
void EnemyBase::Ijike(float delta_second)
{

}

//���S����
void EnemyBase::Die(float delta_second)
{

}

//�ҋ@���
void EnemyBase::Wait(float delta_second)
{

}

//�A�j���[�V�����R���g���[��
void EnemyBase::AnimControl()
{

}

//�G�̏�Ԑ؂�ւ�
void EnemyBase::ChangeMode()
{

}

//�G�̍s����Ԏ擾����
eEnemyState EnemyBase::GetEnemyState()
{

}

//�v���C���[�̏���ϐ��ɂ����
void SetPlayer(Player* p)
{

}
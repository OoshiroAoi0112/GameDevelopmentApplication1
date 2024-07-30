#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

//�R���X�g���N�^
EnemyBase::EnemyBase() :
	nawabari_loc(0.0f),
	state(E_WAIT),
	name(AKABE),
	dirction(UP),
	speed(0),
	player(nullptr),
	spawn_loc(0.0f),
	move_animation(),
	eye_animation(),
	wait_time(),
	eye(),
	flash_count(0),
	gate(false),
	mode_time(0.0f),
	anim_time(0.0f)
{
}

//�f�X�g���N�^
EnemyBase::~EnemyBase()
{
}

//����������
void EnemyBase::Initialize()
{

	//�A�j���[�V�����摜�̓ǂݍ���
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	//�����摜�̐ݒ�
	image = move_animation[0];
	eye = eye_animation[dirction];


	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	//���C���[�̐ݒ�
	z_layer = 4;

	//�����̐ݒ�
	mobility = eMobilityType::Movable;

	//�G�l�~�[�̃X�e�[�^�X
	speed = 5.0f;
	spawn_loc = (0.0f);
	wait_time = 5.0f;
}

//�X�V����
void EnemyBase::Update(float delta_second)
{
	ChangeMode(delta_second);

	Movement(delta_second);

	AnimControl(delta_second);
}

//�`�揈��
void EnemyBase::Draw(const Vector2D& screen_offset)const
{
	__super::Draw(screen_offset);

	if (state != E_IJIKE)
	{
		Vector2D graph_location = this->location + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye, TRUE);
	}
}

//�I������
void EnemyBase::Finalize()
{
	move_animation.clear();
	eye_animation.clear();
}

//Hit����
void EnemyBase::OnHitCollision(GameObjectBase*)
{
	if ((player->GetPowerUp() == true)&&(state == E_IJIKE))
	{
		state = E_DIE;
	}
}

//�ړ�����
void EnemyBase::Movement(float delta_second)
{
	//�G�l�~�[�̏�ԂŁA�����ς���
	switch (state)
	{
		case eEnemyState::E_TUISEKI:
			Tuiseki(delta_second);
			break;
		case eEnemyState::E_NAWABARI:
			Nawabari(delta_second);
			break;
		case eEnemyState::E_IJIKE:
			Ijike(delta_second);
			break;
		case eEnemyState::E_DIE:
			Die(delta_second);
			break;
		case eEnemyState::E_WAIT:
			Wait(delta_second);
			break;	
		default:
			break;
	}
}

//�ǐՃ��[�h
void EnemyBase::Tuiseki(float delta_second)
{
	Vector2D p_loc = player->GetLocation();
	float p_distance = (p_loc.x - location.x * p_loc.x - location.x)+
							(p_loc.y - location.y * p_loc.y - location.y);
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
void EnemyBase::AnimControl(float delta_second)
{
	anim_time += delta_second;
	if (anim_time >= 0.5f)
	{
		anim_time = 0.0f;
		switch (state)
		{
		case E_TUISEKI:
		case E_NAWABARI:
		case E_WAIT:
			if (image == move_animation[0])
			{
				image = move_animation[1];
			}
			else if(image == move_animation[1])
			{
				image = move_animation[0];
			}
			break;

		case E_IJIKE:
			if (image == move_animation[16])
			{
				image = move_animation[17];
			}
			else if (image == move_animation[17])
			{
				image = move_animation[16];
			}
			break;

		case E_DIE:
			image = NULL;
			break;
		default:
			break;
		}
	}
}

//�G�̏�Ԑ؂�ւ�
void EnemyBase::ChangeMode(float delta_second)
{
	mode_time += delta_second;

	switch (state)
	{
	case E_TUISEKI:
		if (mode_time >= 5.0f)
		{
			mode_time = 0.0f;
			state = E_NAWABARI;
		}
		if (player->GetPowerUp() == true)
		{
			mode_time = 0.0f;
			state = E_IJIKE;
			if (image == move_animation[0])
			{
				image = move_animation[16];
			}
			else if (image == move_animation[1])
			{
				image = move_animation[17];
			}
		}
		break;
	case E_NAWABARI:
		if (mode_time >= 4.5f)
		{
			mode_time = 0.0f;
			state = E_TUISEKI;
		}
		if (player->GetPowerUp() == true)
		{
			mode_time = 0.0f;
			state = E_IJIKE;
			if (image == move_animation[0])
			{
				image = move_animation[16];
			}
			else if (image == move_animation[1])
			{
				image = move_animation[17];
			}
		}
		break;
	case E_IJIKE:
		if (mode_time >= 6.0f)
		{
			mode_time = 0.0f;
			state = E_TUISEKI;
			player->SetPowerDown();
			if (image == move_animation[16])
			{
				image = move_animation[0];
			}
			if (image == move_animation[17])
			{
				image = move_animation[1];
			}
		}
		break;
	case E_DIE:
		break;
	case E_WAIT:
		if (mode_time >= wait_time)
		{
			mode_time = 0.0f;
			state = E_TUISEKI;
		}
		if (player->GetPowerUp() == true)
			{
				state = E_IJIKE;
				if (image == move_animation[0])
				{
					image = move_animation[16];
				}
				else if (image == move_animation[1])
				{
					image = move_animation[17];
				}
			}
		break;
	default:
		break;
	}
}

//�G�̍s����Ԏ擾����
eEnemyState EnemyBase::GetEnemyState() const
{
	return state;
}

//�v���C���[�̏���ϐ��ɂ����
void EnemyBase::SetPlayer(Player* p)
{
	player = p;
}
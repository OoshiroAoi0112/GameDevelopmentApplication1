#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "EnemyType/Akabe.h"
#include "EnemyType/Aosuke.h"
#include "EnemyType/Pinky.h"
#include "EnemyType/Guzuta.h"
#include "DxLib.h"

#define D_ENEMY_SPEED   (51.0f)

//�R���X�g���N�^
EnemyBase::EnemyBase() :
	nawabari_loc(0.0f),
	state(E_WAIT),
	name(AKABE),
	direction(LEFT),
	velocity(0.0f),
	speed(0),
	player(nullptr),
	spawn_loc(0.0f),
	branch_panel_x(0),
	branch_panel_y(0),
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
	eye = eye_animation[direction];


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
	speed = D_ENEMY_SPEED;
	spawn_loc = (0.0f);
	wait_time = 5.0f;
}

//�X�V����
void EnemyBase::Update(float delta_second)
{
	//��ԕύX����
	ChangeMode(delta_second);
	//�ړ�����
	Movement(delta_second);
	//�A�j���[�V��������
	AnimControl(delta_second);
}

//�`�揈��
void EnemyBase::Draw(const Vector2D& screen_offset)const
{
	//���S��Ԃł͂Ȃ��Ȃ�̂�`�悷��
	if (state != E_DIE)
	{
		__super::Draw(screen_offset);
	}
	//��������ԂȂ�ڂ�`�悷��
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
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	//�v���C���[�ɓ��������Ƃ��v���C���[���p���[�A�b�v��ԂȂ玀�S��ԂɂȂ�
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		if ((player->GetPowerUp() == true) && (state == E_IJIKE))
		{
			state = E_DIE;
		}
	}
	
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		//SetDirection();
		// �����蔻������擾���āA�J�v�Z��������ʒu�����߂�
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// �ŋߖT�_�����߂�
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Player����near_point�ւ̕����x�N�g�����擾
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// �߂荞�񂾍���
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diff�̕������߂�
		location += dv.Normalize() * diff;

		//SetDirection();
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

	//�s�����������ɍ��킹�Ĉړ��ʂ�ς���
	switch (direction)
	{
	case EnemyBase::UP:
		velocity.y = -1.0f;
		velocity.x = 0.0f;
		break;
	case EnemyBase::DOWN:
		velocity.y = 1.0f;
		velocity.x = 0.0f;
		break;
	case EnemyBase::LEFT:
		velocity.x = -1.0f;
		velocity.y = 0.0f;
		break;
	case EnemyBase::RIGHT:
		velocity.x = 1.0f;
		velocity.y = 0.0f;
		break;
	}
}

//�ǐՃ��[�h
void EnemyBase::Tuiseki(float delta_second)
{
	//���݂̃p�l���ʒu���u�����`�Ȃ�����ύX�������Ă�
	if (StageData::GetPanelData(location) == ePanelID::BRANCH)
	{
		SetDirection(player->GetLocation());
	}
	//���݂̃p�l���ʒu���Q�[�g�Ȃ�ړ����x��80%�ɂȂ�
	if (StageData::GetPanelData(location) == ePanelID::GATE)
	{
		speed=(float)(D_ENEMY_SPEED*0.8);
	}
	else
	{
		speed = D_ENEMY_SPEED;
	}

	location += velocity * speed * delta_second;

	eye = eye_animation[direction];

	// ��ʊO�ɍs������A���Α��Ƀ��[�v������
	if (location.x < 0.0f)
	{
		location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}
}

//�꒣�胂�[�h
void EnemyBase::Nawabari(float delta_second)
{
	//���݂̃p�l���ʒu���u�����`�Ȃ�����ύX�������Ă�
	if (StageData::GetPanelData(location) == ePanelID::BRANCH)
	{
		SetDirection(Vector2D(0.0f,0.0f));
	}
	//���݂̃p�l���ʒu���Q�[�g�Ȃ�ړ����x��80%�ɂȂ�
	if (StageData::GetPanelData(location) == ePanelID::GATE)
	{
		speed = (float)(D_ENEMY_SPEED * 0.8);
	}
	else
	{
		speed = D_ENEMY_SPEED;
	}

	location += velocity * speed * delta_second;

	eye = eye_animation[direction];

	// ��ʊO�ɍs������A���Α��Ƀ��[�v������
	if (location.x < 0.0f)
	{
		location.x = 672.0f;
		location.x = 672.0f - collision.radius;
		velocity.y = 0.0f;
	}
	if (672.0f < location.x)
	{
		location.x = 0.0f;
		location.x = collision.radius;
		velocity.y = 0.0f;
	}
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

//
void EnemyBase::SetDirection(Vector2D destination)
{
	int x, y;
	StageData::ConvertToIndex(location, y, x);

	//���݂̃u�����`�p�l�����O��̃u�����`�ʒu�Ɠ����ł͖�����
	if (branch_panel_x != x || branch_panel_y != y)
	{
		//���݈ʒu�̏㉺���E�̃p�l�������擾
		std::map<eAdjacentDirection, ePanelID> panel = {
								{ eAdjacentDirection::UP, ePanelID::NONE },
								{ eAdjacentDirection::DOWN, ePanelID::NONE },
								{ eAdjacentDirection::LEFT, ePanelID::NONE },
								{ eAdjacentDirection::RIGHT, ePanelID::NONE }
		};
		panel = StageData::GetAdjacentPanelData(location);

		//�ړI�n�̃p�l���ʒu���擾
		int Panel_x, Panel_y;
		StageData::ConvertToIndex(destination, Panel_y, Panel_x);

		//���̈ړ�����
		eEnemyDirection next_direction=direction;
		//�u�����`�p�l���̒����l
		int branch_loc = 0;

		//���݂̈ړ��������㉺�Ȃ�
		if (direction == UP || direction == DOWN)
		{
			//�u�����`�p�l��Y���������W���C���g�^�Ŏ擾
			branch_loc = (int)(y * D_OBJECT_SIZE + D_OBJECT_SIZE / 2);
			//���݂�Y���ʒu���C���g�^�Ŏ擾
			int location_y = ((int)location.y);

			//���݂�Y���ʒu���u�����`�p�l���̒����l�Ȃ�
			if (location_y == branch_loc)
			{
				//�E���ǂł͂Ȃ�
				if (panel[eAdjacentDirection::RIGHT] != ePanelID::WALL)
				{
					//�ړI�n�����g���E���ɂ���
					if (destination.x >= location.x)
					{
						next_direction = RIGHT;
					}
				}
				//�����ǂł͂Ȃ�
				if (panel[eAdjacentDirection::DOWN] != ePanelID::WALL && direction != UP)
				{
					//�ړI�n�����g��艺�ɂ���
					if (destination.y >= location.y)
					{
						next_direction = DOWN;
					}
				}
				//�����ǂł͂Ȃ�
				if (panel[eAdjacentDirection::LEFT] != ePanelID::WALL)
				{
					//�ړI�n�����g��荶�ɂ���
					if (destination.x <= location.x)
					{
						next_direction = LEFT;
					}
				}
				//�オ�ǂł͂Ȃ�
				if (panel[eAdjacentDirection::UP] != ePanelID::WALL && direction!=DOWN)
				{
					//�ړI�n�����g����ɂ���
					if (destination.y <= location.y)
					{
						next_direction = UP;
					}
				}

				//�ړ�������ύX
				direction = next_direction;

				//�g�p�����u�����`�p�l����o�^
				branch_panel_x = x;
				branch_panel_y = y;
			}
		}
		//���݂̈ړ����������E�Ȃ�
		else if (direction == LEFT || direction == RIGHT)
		{
			//�u�����`�p�l��X���������W���C���g�^�Ŏ擾
			branch_loc = (int)(x * D_OBJECT_SIZE + D_OBJECT_SIZE / 2);
			//���݂�X���ʒu���C���g�^�Ŏ擾
			int location_x = ((int)location.x);

			//���݂�X���ʒu���u�����`�p�l���̒����l�Ȃ�
			if (location_x == branch_loc)
			{
				//�E���ǂł͂Ȃ�
				if (panel[eAdjacentDirection::RIGHT] != ePanelID::WALL)
				{
					//�ړI�n�����g���E���ɂ���
					if (destination.x >= location.x)
					{
						next_direction = RIGHT;
					}
				}
				//�����ǂł͂Ȃ�
				if (panel[eAdjacentDirection::DOWN] != ePanelID::WALL && direction != UP)
				{
					//�ړI�n�����g��艺�ɂ���
					if (destination.y >= location.y)
					{
						next_direction = DOWN;
					}
				}
				//�����ǂł͂Ȃ�
				if (panel[eAdjacentDirection::LEFT] != ePanelID::WALL)
				{
					//�ړI�n�����g��荶�ɂ���
					if (destination.x <= location.x)
					{
						next_direction = LEFT;
					}
				}
				//�オ�ǂł͂Ȃ�
				if (panel[eAdjacentDirection::UP] != ePanelID::WALL && direction != DOWN)
				{
					//�ړI�n�����g����ɂ���
					if (destination.y <= location.y)
					{
						next_direction = UP;
					}
				}

				//�ړ�������ύX
				direction = next_direction;

				//�g�p�����u�����`�p�l����o�^
				branch_panel_x = x;
				branch_panel_y = y;
			}
		}
	}
}

//�A�j���[�V�����R���g���[��
void EnemyBase::AnimControl(float delta_second)
{
	anim_time += delta_second;
	//0.5�b�Ɉ�x�A�j���[�V����
	if (anim_time >= 0.5f)
	{
		//�A�j���[�V�����^�C�������Z�b�g
		anim_time = 0.0f;

		//���g�̏�Ԃɂ���ăA�j���[�V������ς���
		switch (state)
		{
		case E_TUISEKI:
		case E_NAWABARI:
		case E_WAIT:
			if (image == move_animation[name*2])
			{
				image = move_animation[name*2+1];
			}
			else if(image == move_animation[name*2+1])
			{
				image = move_animation[name*2];
			}
			break;

		case E_IJIKE:
			//��������Ԃ�6�b�ȓ��Ȃ�
			if (mode_time < 6.0)
			{
				if (image == move_animation[16])
				{
					image = move_animation[17];
				}
				else if (image == move_animation[17])
				{
					image = move_animation[16];
				}
			}
			//��������Ԃ�6�b�𒴂�����
			else if (mode_time >= 6.0)
			{
				//�_�ŉ񐔂�0�ُ�Ȃ�
				if (flash_count >= 0)
				{
					//�_�ŉ񐔂̎c�肪0���́A2�̔{���Ȃ�
					if (flash_count % 2 == 0)
					{
						if (image == move_animation[16])
						{
							image = move_animation[19];
							flash_count--;
						}
						if (image == move_animation[17])
						{
							image = move_animation[18];
							flash_count--;
						}
					}
					//�_�ŉ񐔂̎c�肪��Ȃ�
					else if (flash_count % 2 == 1)
					{
						if (image == move_animation[19])
						{
							image = move_animation[16];
							flash_count--;
						}
						if (image == move_animation[18])
						{
							image = move_animation[17];
							flash_count--;
						}
					}
				}
				//�c��̓_�ŉ񐔂�0��菭�Ȃ��Ȃ�
				else
				{
					//��ԕύX���Ԃ����Z�b�g
					mode_time = 0.0f;
					//��Ԃ�ǐՏ�ԂɕύX
					state = E_TUISEKI;
					//�v���C���[�̃p���[�A�b�v��Ԃ�false�ɂ���
					player->SetPowerDown();
					if (image == move_animation[19])
					{
						image = move_animation[name * 2];
					}
					if (image == move_animation[18])
					{
						image = move_animation[name * 2+1];
					}
				}
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
	//��ԕύX���Ԃ�1�t���[��/�b�����Z
	mode_time += delta_second;

	//��Ԃɂ���ď�ԕύX�^�C�~���O��ς���
	switch (state)
	{
	case E_TUISEKI:
		if (mode_time >= 15.0f)
		{
			//��ԕύX���Ԃ����Z�b�g
			mode_time = 0.0f;
			//�꒣��ԂɕύX
			state = E_NAWABARI;
		}
		//�v���C���[���p���[�a�����Ƃ�������ԂɂȂ�
		if (player->GetPowerUp() == true)
		{
			mode_time = 0.0f;
			state = E_IJIKE;
			//�_�ŉ񐔂��w��
			flash_count = 8;
			//���݂̑��摜�ɍ��킹�Ă������摜��ύX
			if (image == move_animation[name*2])
			{
				image = move_animation[16];
			}
			else if (image == move_animation[name*2+1])
			{
				image = move_animation[17];
			}
		}
		break;
	case E_NAWABARI:
		if (mode_time >= 6.5f)
		{
			//��ԕύX���Ԃ����Z�b�g
			mode_time = 0.0f;
			//�ǐՏ�ԂɕύX
			state = E_TUISEKI;
		}
		//�v���C���[���p���[�a�����Ƃ�������ԂɂȂ�
		if (player->GetPowerUp() == true)
		{
			mode_time = 0.0f;
			state = E_IJIKE;
			//�_�ŉ񐔂��w��
			flash_count = 8;
			//���݂̑��摜�ɍ��킹�Ă������摜��ύX
			if (image == move_animation[name * 2])
			{
				image = move_animation[16];
			}
			else if (image == move_animation[name * 2 + 1])
			{
				image = move_animation[17];
			}
		}
		break;
	case E_IJIKE:
		break;
	case E_DIE:
		break;
	case E_WAIT:
		if (mode_time >= wait_time)
		{
			mode_time = 0.0f;
			state = E_TUISEKI;
		}
		//�v���C���[���p���[�a�����Ƃ�������ԂɂȂ�
		if (player->GetPowerUp() == true)
		{
			mode_time = 0.0f;
			state = E_IJIKE;
			//�_�ŉ񐔂��w��
			flash_count = 8;
			//���݂̑��摜�ɍ��킹�Ă������摜��ύX
			if (image == move_animation[name * 2])
			{
				image = move_animation[16];
			}
			else if (image == move_animation[name * 2 + 1])
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

void EnemyBase::SetName()
{
	//�����ʒu�ɍ��킹�Ė��O��ς���
	int x = 0, y = 0;
	StageData::ConvertToIndex(location, y, x);
	switch (x)
	{
	case 13:
		name = AKABE;
		break;
	case 14:
		name = PINKY;
		break;
	case 12:
		name = AOSUKE;
		break;
	case 16:
		name = GUZUTA;
		break;
	default:
		break;
	}
	image = move_animation[name * 2];
}

//�v���C���[�̏���ϐ��ɂ����
void EnemyBase::SetPlayer(Player* p)
{
	player = p;
}
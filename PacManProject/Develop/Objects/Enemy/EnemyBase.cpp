#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"

//コンストラクタ
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

//デストラクタ
EnemyBase::~EnemyBase()
{
}

//初期化処理
void EnemyBase::Initialize()
{

	//アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);

	//初期画像の設定
	image = move_animation[0];
	eye = eye_animation[dirction];


	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	//レイヤーの設定
	z_layer = 4;

	//可動性の設定
	mobility = eMobilityType::Movable;

	//エネミーのステータス
	speed = 5.0f;
	spawn_loc = (0.0f);
	wait_time = 5.0f;
}

//更新処理
void EnemyBase::Update(float delta_second)
{
	ChangeMode(delta_second);

	Movement(delta_second);

	AnimControl(delta_second);
}

//描画処理
void EnemyBase::Draw(const Vector2D& screen_offset)const
{
	__super::Draw(screen_offset);

	if (state != E_IJIKE)
	{
		Vector2D graph_location = this->location + screen_offset;
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye, TRUE);
	}
}

//終了処理
void EnemyBase::Finalize()
{
	move_animation.clear();
	eye_animation.clear();
}

//Hit処理
void EnemyBase::OnHitCollision(GameObjectBase*)
{
	if ((player->GetPowerUp() == true)&&(state == E_IJIKE))
	{
		state = E_DIE;
	}
}

//移動処理
void EnemyBase::Movement(float delta_second)
{
	//エネミーの状態で、動作を変える
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

//追跡モード
void EnemyBase::Tuiseki(float delta_second)
{
	Vector2D p_loc = player->GetLocation();
	float p_distance = (p_loc.x - location.x * p_loc.x - location.x)+
							(p_loc.y - location.y * p_loc.y - location.y);
}

//縄張りモード
void EnemyBase::Nawabari(float delta_second)
{

}

//いじけ状態
void EnemyBase::Ijike(float delta_second)
{

}

//死亡処理
void EnemyBase::Die(float delta_second)
{

}

//待機状態
void EnemyBase::Wait(float delta_second)
{

}

//アニメーションコントロール
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

//敵の状態切り替え
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

//敵の行動状態取得処理
eEnemyState EnemyBase::GetEnemyState() const
{
	return state;
}

//プレイヤーの情報を変数にいれる
void EnemyBase::SetPlayer(Player* p)
{
	player = p;
}
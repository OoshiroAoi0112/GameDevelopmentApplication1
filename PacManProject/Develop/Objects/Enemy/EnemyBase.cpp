#include "EnemyBase.h"
#include "../../Utility/ResourceManager.h"
#include "EnemyType/Akabe.h"
#include "EnemyType/Aosuke.h"
#include "EnemyType/Pinky.h"
#include "EnemyType/Guzuta.h"
#include "DxLib.h"

#define D_ENEMY_SPEED   (51.0f)

//コンストラクタ
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
	eye = eye_animation[direction];


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
	speed = D_ENEMY_SPEED;
	spawn_loc = (0.0f);
	wait_time = 5.0f;
}

//更新処理
void EnemyBase::Update(float delta_second)
{
	//状態変更処理
	ChangeMode(delta_second);
	//移動処理
	Movement(delta_second);
	//アニメーション処理
	AnimControl(delta_second);
}

//描画処理
void EnemyBase::Draw(const Vector2D& screen_offset)const
{
	//死亡状態ではないなら体を描画する
	if (state != E_DIE)
	{
		__super::Draw(screen_offset);
	}
	//いじけ状態なら目を描画する
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
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	//プレイヤーに当たったときプレイヤーがパワーアップ状態なら死亡状態になる
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
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;

		//SetDirection();
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

	//行きたい方向に合わせて移動量を変える
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

//追跡モード
void EnemyBase::Tuiseki(float delta_second)
{
	//現在のパネル位置がブランチなら方向変更処理を呼ぶ
	if (StageData::GetPanelData(location) == ePanelID::BRANCH)
	{
		SetDirection(player->GetLocation());
	}
	//現在のパネル位置がゲートなら移動速度が80%になる
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

	// 画面外に行ったら、反対側にワープさせる
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

//縄張りモード
void EnemyBase::Nawabari(float delta_second)
{
	//現在のパネル位置がブランチなら方向変更処理を呼ぶ
	if (StageData::GetPanelData(location) == ePanelID::BRANCH)
	{
		SetDirection(Vector2D(0.0f,0.0f));
	}
	//現在のパネル位置がゲートなら移動速度が80%になる
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

	// 画面外に行ったら、反対側にワープさせる
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

//
void EnemyBase::SetDirection(Vector2D destination)
{
	int x, y;
	StageData::ConvertToIndex(location, y, x);

	//現在のブランチパネルが前回のブランチ位置と同じでは無いか
	if (branch_panel_x != x || branch_panel_y != y)
	{
		//現在位置の上下左右のパネル情報を取得
		std::map<eAdjacentDirection, ePanelID> panel = {
								{ eAdjacentDirection::UP, ePanelID::NONE },
								{ eAdjacentDirection::DOWN, ePanelID::NONE },
								{ eAdjacentDirection::LEFT, ePanelID::NONE },
								{ eAdjacentDirection::RIGHT, ePanelID::NONE }
		};
		panel = StageData::GetAdjacentPanelData(location);

		//目的地のパネル位置を取得
		int Panel_x, Panel_y;
		StageData::ConvertToIndex(destination, Panel_y, Panel_x);

		//次の移動方向
		eEnemyDirection next_direction=direction;
		//ブランチパネルの中央値
		int branch_loc = 0;

		//現在の移動方向が上下なら
		if (direction == UP || direction == DOWN)
		{
			//ブランチパネルY軸中央座標をイント型で取得
			branch_loc = (int)(y * D_OBJECT_SIZE + D_OBJECT_SIZE / 2);
			//現在のY軸位置をイント型で取得
			int location_y = ((int)location.y);

			//現在のY軸位置がブランチパネルの中央値なら
			if (location_y == branch_loc)
			{
				//右が壁ではない
				if (panel[eAdjacentDirection::RIGHT] != ePanelID::WALL)
				{
					//目的地が自身より右側にある
					if (destination.x >= location.x)
					{
						next_direction = RIGHT;
					}
				}
				//下が壁ではない
				if (panel[eAdjacentDirection::DOWN] != ePanelID::WALL && direction != UP)
				{
					//目的地が自身より下にある
					if (destination.y >= location.y)
					{
						next_direction = DOWN;
					}
				}
				//左が壁ではない
				if (panel[eAdjacentDirection::LEFT] != ePanelID::WALL)
				{
					//目的地が自身より左にある
					if (destination.x <= location.x)
					{
						next_direction = LEFT;
					}
				}
				//上が壁ではない
				if (panel[eAdjacentDirection::UP] != ePanelID::WALL && direction!=DOWN)
				{
					//目的地が自身より上にある
					if (destination.y <= location.y)
					{
						next_direction = UP;
					}
				}

				//移動方向を変更
				direction = next_direction;

				//使用したブランチパネルを登録
				branch_panel_x = x;
				branch_panel_y = y;
			}
		}
		//現在の移動方向が左右なら
		else if (direction == LEFT || direction == RIGHT)
		{
			//ブランチパネルX軸中央座標をイント型で取得
			branch_loc = (int)(x * D_OBJECT_SIZE + D_OBJECT_SIZE / 2);
			//現在のX軸位置をイント型で取得
			int location_x = ((int)location.x);

			//現在のX軸位置がブランチパネルの中央値なら
			if (location_x == branch_loc)
			{
				//右が壁ではない
				if (panel[eAdjacentDirection::RIGHT] != ePanelID::WALL)
				{
					//目的地が自身より右側にある
					if (destination.x >= location.x)
					{
						next_direction = RIGHT;
					}
				}
				//下が壁ではない
				if (panel[eAdjacentDirection::DOWN] != ePanelID::WALL && direction != UP)
				{
					//目的地が自身より下にある
					if (destination.y >= location.y)
					{
						next_direction = DOWN;
					}
				}
				//左が壁ではない
				if (panel[eAdjacentDirection::LEFT] != ePanelID::WALL)
				{
					//目的地が自身より左にある
					if (destination.x <= location.x)
					{
						next_direction = LEFT;
					}
				}
				//上が壁ではない
				if (panel[eAdjacentDirection::UP] != ePanelID::WALL && direction != DOWN)
				{
					//目的地が自身より上にある
					if (destination.y <= location.y)
					{
						next_direction = UP;
					}
				}

				//移動方向を変更
				direction = next_direction;

				//使用したブランチパネルを登録
				branch_panel_x = x;
				branch_panel_y = y;
			}
		}
	}
}

//アニメーションコントロール
void EnemyBase::AnimControl(float delta_second)
{
	anim_time += delta_second;
	//0.5秒に一度アニメーション
	if (anim_time >= 0.5f)
	{
		//アニメーションタイムをリセット
		anim_time = 0.0f;

		//自身の状態によってアニメーションを変える
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
			//いじけ状態が6秒以内なら
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
			//いじけ状態が6秒を超えたら
			else if (mode_time >= 6.0)
			{
				//点滅回数が0異常なら
				if (flash_count >= 0)
				{
					//点滅回数の残りが0又は、2の倍数なら
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
					//点滅回数の残りが奇数なら
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
				//残りの点滅回数が0より少ないなら
				else
				{
					//状態変更時間をリセット
					mode_time = 0.0f;
					//状態を追跡状態に変更
					state = E_TUISEKI;
					//プレイヤーのパワーアップ状態をfalseにする
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

//敵の状態切り替え
void EnemyBase::ChangeMode(float delta_second)
{
	//状態変更時間に1フレーム/秒を加算
	mode_time += delta_second;

	//状態によって状態変更タイミングを変える
	switch (state)
	{
	case E_TUISEKI:
		if (mode_time >= 15.0f)
		{
			//状態変更時間をリセット
			mode_time = 0.0f;
			//縄張状態に変更
			state = E_NAWABARI;
		}
		//プレイヤーがパワー餌を取るといじけ状態になる
		if (player->GetPowerUp() == true)
		{
			mode_time = 0.0f;
			state = E_IJIKE;
			//点滅回数を指定
			flash_count = 8;
			//現在の足画像に合わせていじけ画像を変更
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
			//状態変更時間をリセット
			mode_time = 0.0f;
			//追跡状態に変更
			state = E_TUISEKI;
		}
		//プレイヤーがパワー餌を取るといじけ状態になる
		if (player->GetPowerUp() == true)
		{
			mode_time = 0.0f;
			state = E_IJIKE;
			//点滅回数を指定
			flash_count = 8;
			//現在の足画像に合わせていじけ画像を変更
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
		//プレイヤーがパワー餌を取るといじけ状態になる
		if (player->GetPowerUp() == true)
		{
			mode_time = 0.0f;
			state = E_IJIKE;
			//点滅回数を指定
			flash_count = 8;
			//現在の足画像に合わせていじけ画像を変更
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

//敵の行動状態取得処理
eEnemyState EnemyBase::GetEnemyState() const
{
	return state;
}

void EnemyBase::SetName()
{
	//生成位置に合わせて名前を変える
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

//プレイヤーの情報を変数にいれる
void EnemyBase::SetPlayer(Player* p)
{
	player = p;
}
#include "Enemy.h"
#include "EnemyType/Hako.h"
#include "EnemyType/Hane.h"
#include "EnemyType/Harpy.h"
#include "EnemyType/Gold.h"
#include "../../Utility/InputControl.h"
#include <math.h>
#include "DxLib.h"


//コンストラクタ
Enemy::Enemy() :animation_count(0), flip_flag(FALSE),hit(false),blend(250), give_score(0)
{
	for (int i = 0; i < 5; i++)
	{
		animation[i] = NULL;               //敵の画像（金敵のみ5枚）
		init_enemy_y[i] = i * 50 + 180;    //敵が出現するy座標
	}
	score[HAKO] = 200;
	score[HANE] = 30;
	score[HARPY] = -100;
	score[GOLD] = 1500;
}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{

}

//更新処理
void Enemy::Update()
{
	//動けるかどうか
	if (hit == false)
	{
		//移動処理
		Movement();
	}
	//アニメーション制御
	AnimeControl();
}

//描画処理
void Enemy::Draw()const
{
	//被弾したなら
	if (hit == true)
	{
		//描画モードをアルファブレンドにする
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, blend);
	}
	//エネミー画像の描画
	DrawRotaGraphF(location.x, location.y, 0.6, radian, image, TRUE, flip_flag);
	
	SetDrawBlendMode(DX_BLENDGRAPHTYPE_NORMAL,0);

	//デバッグ用
#if _DEBUG
	//辺り判定の可視化
	Vector2D box_collision_upper_left = location - box_size / 2.0f;
	Vector2D box_collision_lower_right = location + box_size / 2.0f;

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Enemy::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Enemy::OnHitCollision(GameObject* hit_object)
{
	int type = hit_object->GetObjectType();
	
	if (type == BULLET)
	{
		//被弾したら動けなくする
		hit = true;
		animation_count = 0;
		box_size = 0.0f;
		give_score = score[create_type];
	}
}

//移動処理
void Enemy::Movement()
{
	//現在の一座標に速さを加算する
	location += velocity;

	//
	if (location.x > 640.0f || location.x < 0.0f)
	{
		//hit = true;
		destroy = true;
	}
}

//アニメーション制御
void Enemy::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;
	if (hit == false)
	{
		//40フレーム目に達したら
		if (animation_count >= 40)
		{
			//カウントのリセット
			animation_count = 0;

			//画像の切り替え
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
			location.x += 10.0f;
		}
		else if (animation_count % 8 == 4)
		{
			location.x -= 10.0f;
		}
		location.y += 0.5f;
		blend = blend - 5;

		//敵の削除
		if (animation_count >= 80)
		{
			destroy = true;
		}
	}
}

int Enemy::GetGiveScore()
{
	return give_score;
}
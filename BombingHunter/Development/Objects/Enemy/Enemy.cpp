#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"


//コンストラクタ
Enemy::Enemy() :animation_count(0), flip_flag(FALSE),hit(false)
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//location = (Vector2D(400.0f, 300.0f));

	//画像の読み込み

	switch (GetObjectType())
	{
		case HAKO:
			animation[0] = LoadGraph("Resource/Images/Enemy/hako/1.png");
			animation[1] = LoadGraph("Resource/Images/Enemy/hako/2.png");
			break;
		case HANE:
			animation[0] = LoadGraph("Resource/Images/Enemy/hane/1.png");
			animation[1] = LoadGraph("Resource/Images/Enemy/hane/2.png");
			break;
		case HARPY:
			animation[0] = LoadGraph("Resource/Images/Enemy/harpy/1.png");
			animation[1] = LoadGraph("Resource/Images/Enemy/harpy/2.png");
			break;
		case GOLD:
			animation[0] = LoadGraph("Resource/Images/Enemy/gold/3.png");
			animation[1] = LoadGraph("Resource/Images/Enemy/gold/5.png");
			break;
	}
	

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコ敵の画像がありません\n");
	}
	//移動量
	velocity.x = 2;

	//向きの設定
	radian = 0.0;

	//大きさの設定
	box_size = 64.0;
	scale = 64.0;

	//初期画像の設定
	image = animation[0];

	//弾に当たったかどうか
	hit = false;

	//消したいかどうか
	destroy = false;
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
		SetDrawBlendMode(DX_BLENDGRAPHTYPE_ALPHA, 255);
	}
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);
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
	//被弾したら動けなくする
	hit = true;
	animation_count = 0;
	box_size = 0.0f;
}

//移動処理
void Enemy::Movement()
{
	////ハコ敵の高さ設定
	//location.y = 480.0f-scale;

	//現在の一座標に速さを加算する
	location += velocity;

	//
	/*if (location.x > 640.0f || location.x < 0.0f)
	{
		velocity.x = -velocity.x;
		if (flip_flag == true)
		{
			flip_flag = false;
		}
		else
		{
			flip_flag = true;
		}
	}*/
	
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
			location.x += 5.0f;
		}
		else if (animation_count % 8 == 4)
		{
			location.x -= 5.0f;
		}
		location.y += 0.5f;
		//敵の削除
		if (animation_count >= 90)
		{
			destroy = true;
			
		}
	}
}

#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Enemy::Enemy() :animation_count(0), flip_flag(FALSE)
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
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Enemy/hako/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/hako/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコ敵の画像がありません\n");
	}
	//移動量
	velocity.x = 4;

	//向きの設定
	radian = 0.0;

	//大きさの設定
	scale = 64.0;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Enemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();
}

//描画処理
void Enemy::Draw()const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//デバッグ用
#if _DEBUG
	//辺り判定の可視化
	Vector2D box_collision_upper_left = location - (Vector2D(1.0f) *
		(float)scale / 2.0f);
	Vector2D box_collision_lower_right = location + (Vector2D(1.0f) *
		(float)scale / 2.0f);

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
	//当たったときの処理
	velocity.x *=-1;

	if (velocity.x < 0)
	{
		flip_flag = TRUE;
	}
	else
	{
		flip_flag = FALSE;
	}
}

//移動処理
void Enemy::Movement()
{
	//ハコ敵の高さ設定
	location.y = 480.0f-scale;

	//現在の一座標に速さを加算する
	location += velocity;

	//右の壁に当たると左の壁から出てくる
	if (location.x > 640.0f)
	{
		location.x = 0.0f;
	}
	if (location.x < 0.0f)
	{
		location.x = 640.0f;
	}
}

//アニメーション制御
void Enemy::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に達したら
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

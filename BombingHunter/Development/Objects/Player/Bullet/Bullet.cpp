#include "Bullet.h"
#include "DxLib.h"

//コンストラクタ
Bullet::Bullet() :speed(4),animation_count(0),anim_active(0),image_count(0)
{
	for (int i=0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//デストラクタ
Bullet::~Bullet()
{

}

//初期化処理
void Bullet::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Player/P_Bullet/bom.png");
	animation[1] = LoadGraph("Resource/Images/Player/P_Bullet/1.png");
	animation[2] = LoadGraph("Resource/Images/Player/P_Bullet/2.png");
	animation[3] = LoadGraph("Resource/Images/Player/P_Bullet/3.png");

	//エラーチェック
	for (int i=0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("プレイヤーの弾画像がありません");
		}
	}
	//向きの設定
	radian =DX_PI_F/2;
	//大きさの設定
	box_size = 32.0f;
	//初期画像の設定
	image = animation[image_count];
}

//更新処理
void Bullet::Update()
{
	if (destroy == false)
	{
		Movement();
	}
	if (image_count <= 3 && anim_active==1)
	{
		AnimeControl();
	}
}

//描画処理
void Bullet::Draw()const
{
	DrawRotaGraph(location.x, location.y, 0.7, radian,image, TRUE, FALSE);

#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Bullet::Finalize()
{
	//使用した画像を解放する
	for (int i=0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//当たり判定通知処理
void Bullet::OnHitCollision(GameObject* hit_object)
{
	//当たったときの処理
	speed = 0;
	radian = 0;
	image_count = 1;
	anim_active = 1;
	destroy = true;
}

//移動処理
void Bullet::Movement()
{
	location.y += speed;
	if (location.y >= 420)
	{
		speed = 0;
		radian = 0;
		image_count = 1;
		anim_active = 1;
	}
}

void Bullet::AnimeControl()
{
	animation_count++;
	if (animation_count >= 30)
	{
		image_count++;
		switch (image_count)
		{
		case 0:
		case 1:
			break;
		case 2:
			destroy = true;
			break;
		case 3:
			anim_active = 0;
			break;
		}
		animation_count = 0;
	}
	image = animation[image_count];
}
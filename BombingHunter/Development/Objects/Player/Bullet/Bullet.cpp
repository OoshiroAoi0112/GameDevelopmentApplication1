#include "Bullet.h"
#include "DxLib.h"
#include "../../Utility/InputControl.h"

//コンストラクタ
Bullet::Bullet() :speed(0.0f),animation_count(0),anim_active(false),image_count(0)
{
	for (int i=0; i < IMAGE_MAX; i++)
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
	for (int i=0; i < IMAGE_MAX; i++)
	{
		if (animation[i] == -1)
		{
			throw("プレイヤーの弾画像がありません");
		}
	}
	if (InputControl::GetKey(KEY_INPUT_RIGHT) || InputControl::GetKeyDown(KEY_INPUT_RIGHT))
	{
		speed = (Vector2D(3.0f,4.0f));
		radian = DX_PI_F / 4;
	}
	else if (InputControl::GetKey(KEY_INPUT_LEFT) || InputControl::GetKeyDown(KEY_INPUT_LEFT))
	{
		speed = (Vector2D(-3.0f, 4.0f));
		radian = DX_PI_F / 4*3;
	}
	else
	{
		speed = (Vector2D(0.0f, 4.0f));
		radian = DX_PI_F / 2;
	}
	//大きさの設定
	box_size = 32.0f;
	//初期画像の設定
	image = animation[image_count];
	//オブジェクトの種類
	object_type = BULLET;
}

//更新処理
void Bullet::Update()
{
	if (hit == false)
	{
		Movement();
	}
	if (image_count <= 4 && anim_active==true)
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
	for (int i=0; i < IMAGE_MAX; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//当たり判定通知処理
void Bullet::OnHitCollision(GameObject* hit_object)
{
	int type = hit_object->GetObjectType();
	
	if (type == ENEMY)
	{
		//当たったときの処理
		speed = 0;
		radian = 0;
		image_count = 1;
		anim_active = true;
		hit = true;
		box_size = 0.0f;
	}
}

//移動処理
void Bullet::Movement()
{
	if (location.x <= 0.0f || location.x >= 640.0f)
	{
		speed.x = 0.0f;
		radian = DX_PI_F / 2;
	}
	location+= speed;
	
	if (location.y >= 400)
	{
		speed = 0;
		radian = 0;
		image_count = 1;
		anim_active = true;
	}
}

void Bullet::AnimeControl()
{
	animation_count++;
	if (animation_count >= 15)
	{
		image_count++;
		switch (image_count)
		{
		case 0:
		case 1:
		case 3:
			break;
		case 2:
			hit = true;
			break;
		case 4:
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

#include "EnemyBullet.h"
#include "math.h"
#include "DxLib.h"

//コンストラクタ
EnemyBullet::EnemyBullet() :
	velocity(0.0f),
	animation_count(0),
	anim_active(false),
	image_count(0)
{
	for (int i = 0; i < 4; i++)
	{
		animation[i] = NULL;
	}
}

//デストラクタ
EnemyBullet::~EnemyBullet()
{

}

//初期化処理
void EnemyBullet::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/Enemy/E_Bullet/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/E_Bullet/eff1.png");
	animation[2] = LoadGraph("Resource/Images/Enemy/E_Bullet/eff2.png");
	animation[3] = LoadGraph("Resource/Images/Enemy/E_Bullet/eff3.png");

	//エラーチェック
	for (int i = 0; i < 4; i++)
	{
		if (animation[i] == -1)
		{
			throw("敵の弾画像がないよ");
		}
	}
	

	//向きの設定
	radian = 0;
	//大きさの背一定
	box_size = 20.0f;
	//初期画像の設定
	image = animation[image_count];  //animation[0]
	//オブジェクトの種類
	object_type = ENEMY_BULLET;
}

//更新処理
void EnemyBullet::Update()
{
	//ヒット状態じゃないならなら移動して、ヒットしたなら爆発のアニメーションを行う
	if (hit == false)
	{
		Movement();
	}
	if (image_count <= 4 && anim_active == true)
	{
		AnimeControl();
	}
}

//描画処理
void EnemyBullet::Draw() const
{
	DrawRotaGraph(location.x, location.y, 0.7, radian, image, TRUE, FALSE);

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
void EnemyBullet::Finalize()
{
	//使用した画像を解放
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(animation[i]);
	}
}

//当たり判定通知処理
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//オブジェクトの種類を取得してそれに応じて当たり判定を行うか決める
	int type=hit_object->GetObjectType();

	if (type == PLAYER)
	{
		velocity = 0.0f;
		image_count = 1;
		anim_active = true;
		hit = true;
		box_size = 0.0f;
	}
}

//移動処理
void EnemyBullet::Movement()
{
	location += velocity;
	if (location.x < 0.0f || location.x>640.0f || location.y < 0.0f)
	{
		velocity = 0.0f;
		destroy = true;
	}
}

//アニメーション制御
void EnemyBullet::AnimeControl()
{
	animation_count++;
	if (animation_count >= 15)
	{
		image_count++;
		switch (image_count)
		{
		case 0:
		case 2:
			break;
		case 1:
			hit = true;
			break;
		case 3:
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

void EnemyBullet::SetDirection(const Vector2D& dir)
{
	Vector2D vec;
	vec.x = (-(location.x - dir.x)) / (60.0f + (location.y / 10));
	velocity.x = vec.x;

	vec.y = (-(location.y - dir.y))/ (60.0f + (location.x / 10));
	velocity.y = vec.y;
}

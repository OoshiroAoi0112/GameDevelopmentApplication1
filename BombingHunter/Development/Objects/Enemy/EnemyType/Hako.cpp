#include "Hako.h"
#include "DxLib.h"

//コンストラクタ
Hako::Hako()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Hako::~Hako()
{

}

//初期化処理
void Hako::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Enemy/hako/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/hako/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコ敵の画像がありません\n");
	}

	////0か1をランダムで取り
	//出現するx座標・移動する向き・画像の向きを決める
	int rand_loc = GetRand(1);
	int vec = GetRand(1) + 2;

	if (rand_loc == 0)
	{
		location.x = 0.0f;
		velocity.x = vec;
		flip_flag = FALSE;
	}
	else
	{
		location.x = 640.0f;
		velocity.x = -vec;
		flip_flag = TRUE;
	}

	location.y = init_enemy_y[4];
	
	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size =52.0f;

	//初期画像の設定
	image = animation[0];

	//弾に当たったかどうか
	hit = false;

	//消したいかどうか
	destroy = false;

	//オブジェクトの種類
	object_type = ENEMY;

	//生成したい敵の番号（名前）
	create_type = HAKO;

	//弾を撃つ間隔
	shot_span = 60;

	__super::Initialize();
}

void Hako::Update()
{
	shot_count++;
	if (shot_count >= shot_span)
	{
		shot_flag = true;
		shot_count = 0;
	}

	__super::Update();
}

////当たり判定通知処理
//void Hako::OnHitCollision(GameObject* hit_object)
//{
//	//hit = true;
//	__super::Enemy::OnHitCollision(hit_object);
//}

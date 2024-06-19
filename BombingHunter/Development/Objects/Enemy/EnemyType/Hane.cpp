#include "Hane.h"
#include "DxLib.h"

//コンストラクタ
Hane::Hane()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Hane::~Hane()
{

}

//初期化処理
void Hane::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Enemy/hane/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/hane/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコ敵の画像がありません\n");
	}


	////0か1をランダムで取り
	//出現するx座標・移動する向き・画像の向きを決める
	int rand_loc = GetRand(1);
	int vec = GetRand(4) + 1;

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
	rand_loc = GetRand(3);
	location.y = init_enemy_y[rand_loc];

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 52.0f;

	//初期画像の設定
	image = animation[0];

	//弾に当たったかどうか
	hit = false;

	//消したいかどうか
	destroy = false;

	//オブジェクトの種類
	object_type = ENEMY;

	//生成したい敵の番号（名前）
	create_type = HANE;
}


////当たり判定通知処理
//void Hane::OnHitCollision(GameObject* hit_object)
//{
//	//hit = true;
//	__super::Enemy::OnHitCollision(hit_object);
//}


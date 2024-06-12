#include "harpy.h"
#include "DxLib.h"

//コンストラクタ
Harpy::Harpy()
{
	animation[0] = NULL;
	animation[1] = NULL;
}

//デストラクタ
Harpy::~Harpy()
{

}

//初期化処理
void Harpy::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Enemy/harpy/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/harpy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコ敵の画像がありません\n");
	}

	////0か1をランダムで取り
	//出現するx座標・移動する向き・画像の向きを決める
	int rand_loc = GetRand(1);
	int vec = GetRand(1) + 1;

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

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//弾に当たったかどうか
	hit = false;

	//消したいかどうか
	destroy = false;

	object_type = ENEMY;

	create_type = HARPY;
}

//当たり判定通知処理
void Harpy::OnHitCollision(GameObject* hit_object)
{
	hit = true;
}

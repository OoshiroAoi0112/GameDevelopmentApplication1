#include "Hako.h"
#include "DxLib.h"

//コンストラクタ
Hako::Hako()
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
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

	//移動量
	velocity.x = GetRand(1) + 2;

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

	flip_flag = FALSE;
}

//当たり判定通知処理
void Hako::OnHitCollision(GameObject* hit_object)
{

}

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

	//移動量
	velocity.x = GetRand(4) + 1;

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
}


//当たり判定通知処理
void Hane::OnHitCollision(GameObject* hit_object)
{

}


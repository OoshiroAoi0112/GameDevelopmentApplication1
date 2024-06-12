#include "Gold.h"
#include "DxLib.h"

//コンストラクタ
Gold::Gold()
{
	image_count = 0;

	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;
}

//デストラクタ
Gold::~Gold()
{

}

//初期化処理
void Gold::Initialize()
{
	animation[0] = LoadGraph("Resource/Images/Enemy/gold/1.png");
	animation[1] = LoadGraph("Resource/Images/Enemy/gold/2.png");
	animation[2] = LoadGraph("Resource/Images/Enemy/gold/3.png");
	animation[3] = LoadGraph("Resource/Images/Enemy/gold/4.png");
	animation[4] = LoadGraph("Resource/Images/Enemy/gold/5.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("ハコ敵の画像がありません\n");
	}

	////0か1をランダムで取り
	//出現するx座標・移動する向き・画像の向きを決める
	int rand_loc = GetRand(1);

	if (rand_loc == 0)
	{
		location.x = 0;
		velocity.x = 4;
		flip_flag = FALSE;
	}
	else
	{
		location.x = 640;
		velocity.x = -4;
		flip_flag = TRUE;
	}

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 24.0f;

	//初期画像の設定
	image = animation[3];

	//弾に当たったかどうか
	hit = false;

	//消したいかどうか
	destroy = false;

	object_type = ENEMY;

	create_type = GOLD;
}

//当たり判定通知処理
void Gold::OnHitCollision(GameObject* hit_object)
{
	hit = true;
}


void Gold::AnimeControl()
{
	//フレームカウントの加算
	animation_count++;
	if (hit == false)
	{
		//20フレームごとに画像の切り替え
		if (animation_count >= 20)
		{
			//フレームカウントのリセット
			animation_count = 0;
			//読み込みたい画像配列の位置を加算
			image_count++;
			//画像配列の末尾を読み込んでいる場合一番最初に戻す
			if (image == animation[4])
			{
				image = animation[0];
				image_count = 0;
			}
			else
			{
				image = animation[image_count];
			}
		}
	}
	//ﾀﾋぬ演出
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
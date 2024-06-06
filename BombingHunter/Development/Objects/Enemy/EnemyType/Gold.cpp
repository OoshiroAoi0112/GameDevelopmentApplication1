#include "Gold.h"
#include "DxLib.h"

//コンストラクタ
Gold::Gold()
{
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

	//移動量
	velocity.x = GetRand(1) + 2;

	//向きの設定
	radian = 0.0f;

	//大きさの設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[3];

	//弾に当たったかどうか
	hit = false;

	//消したいかどうか
	destroy = false;
}

//更新処理
void Gold::Update()
{

}

//描画処理
void Gold::Draw() const
{

}

//終了時処理
void Gold::Finalize()
{

}

//当たり判定通知処理
void Gold::OnHitCollision(GameObject* hit_object)
{

}

//移動処理
void Gold::Movement()
{

}

//アニメーション制御
void Gold::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;
	if (hit == false)
	{
		//40フレーム目に達したら
		if (animation_count >= 40)
		{
			//カウントのリセット
			animation_count = 0;

			//画像の切り替え
			if (image == animation[3])
			{
				image = animation[4];
			}
			else
			{
				image = animation[3];
			}
		}
	}
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
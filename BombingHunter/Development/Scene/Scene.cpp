#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Player/Bullet/Bullet.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Enemy/EnemyType/Hako.h"
#include "../Objects/Enemy/EnemyType/Hane.h"
#include "../Objects/Enemy/EnemyType/Harpy.h"
#include "../Objects/Enemy/EnemyType/Gold.h"
#include "../Objects/Enemy/Bullet/EnemyBullet.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Scene::Scene() :objects(),create_count(0),score(0),s_digit(0)
{
	//背景画像
	back_image = NULL;
	//タイマー画像
	time_image = NULL;
	//スコア文字画像
	s_str_image = NULL;
	//ハイスコア文字画像
	hs_str_image = NULL;
	//ハイフンを含めた数字画像
	for (int i = 0; i < 10; i++)
	{
		number[i] = NULL;
	}

	//敵の種類ごとの最大数
	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		create_enemy[i] = NULL;
	}
	player = NULL;
}

//デストラクタ
Scene::~Scene()
{
	//忘れ帽子
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	//背景画像読み込み
	back_image = LoadGraph("Resource/Images/Stage/bg.png");
	//タイマー画像
	time_image = LoadGraph("Resource/Images/timer/timer.png");
	//スコア文字画像
	s_str_image = LoadGraph("Resource/Images/score/score.png");
	//ハイスコア文字画像
	hs_str_image = LoadGraph("Resource/Images/score/hs.png");
	//ハイフン含めた数字画像
	number[0] = LoadGraph("Resource/Images/number/0.png");
	number[1] = LoadGraph("Resource/Images/number/1.png");
	number[2] = LoadGraph("Resource/Images/number/2.png");
	number[3] = LoadGraph("Resource/Images/number/3.png");
	number[4] = LoadGraph("Resource/Images/number/4.png");
	number[5] = LoadGraph("Resource/Images/number/5.png");
	number[6] = LoadGraph("Resource/Images/number/6.png");
	number[7] = LoadGraph("Resource/Images/number/7.png");
	number[8] = LoadGraph("Resource/Images/number/8.png");
	number[9] = LoadGraph("Resource/Images/number/9.png");
	number[10] = LoadGraph("Resource/Images/number/-.png");
	
	
	if (back_image == -1)
	{
		throw("背景画像が見つかりません");
	}
	if (time_image == -1)
	{
		throw("背景画像が見つかりません");
	}
	if (s_str_image == -1)
	{
		throw("背景画像が見つかりません");
	}
	if (hs_str_image == -1)
	{
		throw("背景画像が見つかりません");
	}
	
	for (int i=0; i < 10; i++)
	{
		if (number[i] == -1)
		{
			throw("背景画像が見つかりません");
		}
	}

	create_enemy[HAKO] = 3;
	create_enemy[HANE] = 3;
	create_enemy[HARPY] = 2;
	create_enemy[GOLD] = 1;

	//プレイヤーを生成する
	player = CreateObject<Player>(Vector2D(320.0f, 50.0f));
}

//更新処理
void Scene::Update()
{
	//敵を生成するためのカウント
	create_count++;
	//1秒に1種類ずつ敵を生成する
	if (create_count >= 60)
	{
		create_count = 0;
		//敵の種類分だけループする
		for (int i = 0; i < ENEMY_TYPE; i++)
		{
			//敵の種類ごとの生成可能数が1以上であるかどうか
			if (create_enemy[i] > 0)
			{
				if (i == HAKO)
				{
					CreateObject<Hako>(Vector2D(0.0f,390.0f));
				}
				if (i == HANE)
				{
					CreateObject<Hane>(Vector2D(0.0f,300.0f));
				}
				if (i == HARPY)
				{
					CreateObject<Harpy>(Vector2D(0.0f,200.0f));
				}
				if (i == GOLD)
				{
					CreateObject<Gold>(Vector2D(0.0f, 400.0f));
				}
				//CreateObject<Enemy>(gene, i); 
				create_enemy[i] -= 1;
			}
		}
	}

	//Fを押すと弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_F))
	{
		CreateObject<Bullet>(Vector2D(objects[0]->GetLocation()));
	}

	//一定間隔で敵が弾を打つ
	for (int i=0;i<objects.size();i++)
	{
		if(objects[i]->GetObjectType() == ENEMY)
		{
			if (objects[i]->GetShotFlag() == true)
			{
				EnemyBullet* obj = CreateObject<EnemyBullet>(Vector2D(objects[i]->GetLocation()));
				obj->SetDirection(player->GetLocation());
				objects[i]->SetShotFlag();
			}
		}
	}

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		if (obj->GetDestroy() == false)
		{
			obj->Update();
		}
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i+1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//オブジェクトの削除
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->GetDestroy())
		{
			if (objects[i]->GetCreateType() < ENEMY_TYPE)
			{
				int type = objects[i]->GetCreateType();
				create_enemy[type]++;
				Enemy* e=dynamic_cast<Enemy*>(objects[i]);
				score+=e->GetGiveScore();
			}
			objects.erase(objects.begin() + i--);
		}
	}
}

//描画処理
void Scene::Draw()const
{
	//背景画像の描画
	DrawExtendGraph(0, 0, 640, 480, back_image, FALSE);
	//タイマー画像の描画
	DrawRotaGraphF(30, 460, 0.7, 0, time_image, TRUE, TRUE);
	//スコア文字画像の描画
	DrawRotaGraphF(190, 460, 1.3, DX_PI_F, s_str_image, TRUE, TRUE, TRUE);

	DrawFormatString(220, 460, GetColor(255, 255, 255), "%d", score);
	//ハイスコア文字画像の描画
	DrawRotaGraphF(400, 460, 1.3, DX_PI_F, hs_str_image, TRUE, TRUE, TRUE);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		//消したい画像を非表示にする
		if (obj->GetDestroy() == false)
		{
			obj->Draw();
		}
	}
}

//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();
}

//当たり判定チェック処理
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;
	
	//距離より大きさが大きい場合い、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}


void Scene::ScoreCal()
{
	if (score >= 10000)
	{
		s_digit = 4;
		
	}
}
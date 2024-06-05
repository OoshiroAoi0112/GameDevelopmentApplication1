#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Player/Bullet/Bullet.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Scene::Scene() :objects(),create_count(0)
{
	back_image = NULL;
	destroy_number = 0;
	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		create_enemy[i] = NULL;
	}
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
	
	if (back_image == -1)
	{
		throw("背景画像が見つかりません");
	}

	for (int i = 0; i < ENEMY_TYPE; i++)
	{
		switch (i)
		{
		case HAKO:
		case HANE:
			create_enemy[i] = 3;
			break;
		case HARPY:
			create_enemy[i] = 2;
			break;
		case GOLD:
			create_enemy[i] = 1;
			break;
		}
	}

	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(100.0f,100.0f),5);
	////敵を生成する
	//CreateObject<Enemy>(Vector2D(400.0f,300.0f));
}

//更新処理
void Scene::Update()
{
	create_count++;
	if (create_count >= 60)
	{
		create_count = 0;
		for (int i = 0; i < ENEMY_TYPE; i++)
		{
			if (create_enemy[i] > 0)
			{
				switch (i)
				{
					case 0:
						CreateObject<Enemy>(Vector2D(40.0f, 420.0f),i);
						create_enemy[i] -= 1;
						break;
					case 1:
						CreateObject<Enemy>(Vector2D(40.0f, 300.0f),i);
						create_enemy[i] -= 1;
						break;
					case 2:
						CreateObject<Enemy>(Vector2D(40.0f, 200.0f),i);
						create_enemy[i] -= 1;
						break;
					case 3:
						CreateObject<Enemy>(Vector2D(40.0f, 100.0f),i);
						create_enemy[i] -= 1;
						break;
				}
				
			}
		}
	}

	//Fを押すと弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_F))
	{
		CreateBullet<Bullet>(Vector2D(objects[0]->GetLocation()));
	}

	//シーンに存在するオブジェクトの更新処理
	for (GameObject* obj : objects)
	{
		if (obj->GetDestroy() == false)
		{
			obj->Update();
		}
	}
	//弾の更新
	destroy_number = 0;
	for (GameObject* bullet : p_bullet)
	{
		if (bullet->GetDestroy() == false)
		{
			bullet->Update();
		}
		destroy_number++;
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 1; i < objects.size(); i++)
	{
		//当たり判定チェック処理
		HitCheckObject(objects[0], objects[i]);
	}

	//弾と敵同士の当たり判定チェック
	for (GameObject* obj : objects)
	{
		//敵が一度も弾に触れていない状態
		if (!obj->GetHit())
		{
			for (int i = 0; i < p_bullet.size(); i++)
			{
				HitCheckObject(p_bullet[i], obj);
			}
		}
	}

	destroy_number = 0;
	for (GameObject* obj : objects)
	{
		if (obj->GetDestroy())
		{
			create_enemy[obj->GetObjectType()]++;
			objects.erase(objects.begin() + destroy_number);
			destroy_number--;
		}
		destroy_number++;
	}
	destroy_number = 0;
	for (GameObject* bullet : p_bullet)
	{
		if (bullet->GetDestroy())
		{
			p_bullet.erase(p_bullet.begin() + destroy_number);
			destroy_number--;
		}
		destroy_number++;
	}
	destroy_number = 0;
}

//描画処理
void Scene::Draw()const
{
	//背景画像の描画
	DrawExtendGraph(0, 0, 640, 520, back_image, FALSE);

	//シーンに存在するオブジェクトの描画処理
	for (GameObject* obj : objects)
	{
		//消したい画像を非表示にする
		if (obj->GetDestroy() == false)
		{
			obj->Draw();
		}
	}

	//画面に存在する弾の描画
	for (GameObject* bullet : p_bullet)
	{
		//消したい画像を非表示にする
		if (bullet->GetDestroy() == false)
		{
			bullet->Draw();
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
	if (p_bullet.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}
	for (GameObject* bullet : p_bullet)
	{
		bullet->Finalize();
		delete bullet;
	}

	//動的配列の解放
	objects.clear();

	p_bullet.clear();
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
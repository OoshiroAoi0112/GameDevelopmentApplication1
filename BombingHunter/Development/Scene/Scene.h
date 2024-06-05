#pragma once
#define HAKO  (0)
#define HANE  (1)
#define HARPY (2)
#define GOLD  (3)
#define ENEMY_TYPE  (4)

#include <vector>
#include <string>
#include "../Objects/GameObject.h"

class Scene
{
private:
	std::vector<GameObject*>objects;
	std::vector<GameObject*>p_bullet;
	int back_image;
	int create_enemy[ENEMY_TYPE];
	int create_count;
	int destroy_number;

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw()const;
	void Finalize();

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理  //引数const Vector2D& location
	template<class T>
	T* CreateObject(const Vector2D& location,int object_type)
	{
		//指定したクラスを生成する
		T* new_instance = new T();

		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//
		new_object->SetObjectType(object_type);
		//初期化処理
		new_object->Initialize();
		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}

	template<class B>
	B* CreateBullet(const Vector2D& location)
	{
		//指定したクラスを生成する
		B* new_instance = new B();

		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw std::string("ゲームオブジェクトが生成できませんでした");
		}

		//初期化処理
		new_object->Initialize();
		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		p_bullet.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};


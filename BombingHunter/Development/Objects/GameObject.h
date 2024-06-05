#pragma once
#include "../Utility/Vector2D.h"

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location; //位置情報
	Vector2D box_size; //大きさ
	double scale;      //大きさ
	double radian;     //向き
	int image;         //描画する画像
	int sound;         //再生する音源
	bool hit;          //オブジェクトに当たり判定が残っているか
	bool destroy;      //オブジェクトを壊したいか
	int object_type;   //オブジェクトの種類

public:
	GameObject();
	virtual ~GameObject();

	virtual void Initialize();     //初期化処理
	virtual void Update();         //更新処理
	virtual void Draw() const;     //描画処理
	virtual void Finalize();       //終了処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;
	//当たり判定の有無
	bool GetHit()const;
	//オブジェクトを消したいかどうか
	bool GetDestroy()const;
	//オブジェクトサイズ取得
	Vector2D GetBoxSize() const;

	int GetObjectType() const;
	//位置情報変更処理
	void SetLocation(const Vector2D& locaiton);

	void SetObjectType(int object_type);
};


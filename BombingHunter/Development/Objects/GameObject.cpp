#include "GameObject.h"
//コンストラクタ
GameObject::GameObject() :
	location(0.0f),
	scale(0.0),
	radian(0.0),
	image(0),
	sound(0),
	hit(false),
	destroy(false),
	object_type(0),
	create_type(5)
{

}

//デストラクタ
GameObject::~GameObject()
{

}

//初期化処理
void GameObject::Initialize()
{

}

//更新処理
void GameObject::Update()
{

}

//描画処理
void GameObject::Draw() const
{

}

//終了時処理
void GameObject::Finalize()
{

}

//当たり判定処理通知処理
void GameObject::OnHitCollision(GameObject* hit_object)
{
	//当たったときに行う処理

}

//位置情報取得処理
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

//オブジェクトサイズ取得
Vector2D GameObject::GetBoxSize() const
{
	return this->box_size;
}

//オブジェクトの種類取得
int GameObject::GetObjectType() const
{
	return object_type;
}

//生成したい敵の種類取得
int GameObject::GetCreateType() const
{
	return create_type;
}

//ヒットした状態か取得
bool GameObject::GetHit() const
{
	return hit;
}

//消したいかどうか取得
bool GameObject::GetDestroy() const
{
	return destroy;
}

//位置情報設定処理
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}
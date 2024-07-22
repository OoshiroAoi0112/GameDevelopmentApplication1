#include "EnemyBase.h"
#include "DxLib.h"

//コンストラクタ
EnemyBase::EnemyBase() :
	nawabari_loc(0.0f),
	state(WAIT),
	speed(5),
	player(nullptr),
	spawn_loc(0.0f),
	move_animation(),
	eye_animation(),
	flash_count(0),
	gate(false),
	mode_time(0.0f),
	anim_count(0.0f)
{
}

//デストラクタ
EnemyBase::~EnemyBase()
{
}

//初期化処理
void EnemyBase::Initialize()
{

}

//更新処理
void EnemyBase::Update(float delta_second)
{

}

//Hit処理
void EnemyBase::OnHitCollision(GameObjectBase*)
{

}

//描画処理
void EnemyBase::Draw(const Vector2D&)const
{

}

//終了処理
void EnemyBase::Finalize()
{

}

//移動処理
void EnemyBase::Movement(float delta_second)
{

}

//追跡モード
void EnemyBase::Tuiseki(float delta_second)
{

}

//縄張りモード
void EnemyBase::Nawabari(float delta_second)
{

}

//いじけ状態
void EnemyBase::Ijike(float delta_second)
{

}

//死亡処理
void EnemyBase::Die(float delta_second)
{

}

//待機状態
void EnemyBase::Wait(float delta_second)
{

}

//アニメーションコントロール
void EnemyBase::AnimControl()
{

}

//敵の状態切り替え
void EnemyBase::ChangeMode()
{

}

//敵の行動状態取得処理
eEnemyState EnemyBase::GetEnemyState()
{

}

//プレイヤーの情報を変数にいれる
void SetPlayer(Player* p)
{

}
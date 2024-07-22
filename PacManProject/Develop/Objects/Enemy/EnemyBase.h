#pragma once

#include "../GameObject.h"
#include "../Player/Player.h"

enum eEnemyState   //敵の行動状態
{
	TUISEKI,  //追跡
	NAWABARI, //縄張り
	IJIKE,    //いじけ
	DIE,      //死
	WAIT,     //待機
};

enum eEnemyName   //敵の名前
{
	AKABE,   //アカベー
	PINKEY,  //ピンキー
	AOSUKE,  //アオスケ
	GUZUTA,  //グズタ
};

class EnemyBase : public GameObject
{
public:
	enum eEnemyDirection   //敵の移動方向
	{
		UP,     //上
		LEFT,   //左
		DOWN,   //下
		RIGHT,  //右
	};

protected:
	Vector2D nawabari_loc;  //縄張りの位置
	eEnemyState state;      //行動状態
	float speed;            //足の速さ
	Player* player;         //プレイヤー情報

private:
	Vector2D spawn_loc;              //スタート・リスポーン位置
	std::vector<int> move_animation; //ボディ画像
	std::vector<int> eye_animation;  //目画像
	int flash_count;    //点滅回数
	bool gate;          //ゲート・ワープの範囲内か(範囲内:true,範囲外:false)
	float mode_time;    //各状態の時間
	float anim_count;   //アニメーションカウント


public:
	EnemyBase();           //コンストラクタ
	virtual ~EnemyBase();  //デストラクタ

	virtual void Initialize() override;            //初期化処理
	void Update(float)override;                    //更新処理
	void Draw(const Vector2D&)const override;      //描画
	void Finalize()override;                       //終了処理
	void OnHitCollision(GameObjectBase*)override;  //Hit処理

	eEnemyState GetEnemyState(); //敵の状態取得処理
	void SetPlayer(Player*);     //プレイヤーの情報を変数に入れる

protected:
	virtual void Tuiseki(float);  //追跡状態

private:
	void Movement(float);  //移動処理
	void Nawabari(float);  //縄張り状態
	void Ijike(float);     //いじけ状態
	void Die(float);       //死
	void Wait(float);      //待機状態

	void AnimControl();    //アニメーション処理
	void ChangeMode();     //状態の切り替え
};
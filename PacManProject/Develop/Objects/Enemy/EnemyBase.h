#pragma once

#include "../GameObject.h"
#include "../Player/Player.h"

enum eEnemyState   //敵の行動状態
{
	E_TUISEKI,  //追跡
	E_NAWABARI, //縄張り
	E_IJIKE,    //いじけ
	E_DIE,      //死
	E_WAIT,     //待機
};

enum eEnemyName   //敵の名前
{
	AKABE,   //アカベー
	PINKY,  //ピンキー
	AOSUKE,  //アオスケ
	GUZUTA,  //グズタ
};

/// <summary>
/// エネミークラス（モンスター）
/// </summary>
class EnemyBase : public GameObject
{
public:
	enum eEnemyDirection   //敵の移動方向
	{
		UP,     //上
		RIGHT,   //右
		DOWN,   //下
		LEFT,  //左
	};

protected:
	Vector2D nawabari_loc;     //縄張りの位置
	eEnemyState state;         //行動状態
	eEnemyName name;           //敵の名前
	eEnemyDirection direction;  //敵の移動方向
	Vector2D velocity;
	float speed;               //足の速さ
	Player* player;            //プレイヤー情報
	int eye;                   //体の画像
	float wait_time;           //待機時間
	int branch_panel_x;        //一つ前に使ったブランチパネルx
	int branch_panel_y;        //一つ前に使ったブランチパネルy

private:
	Vector2D spawn_loc;              //スタート・リスポーン位置
	std::vector<int> move_animation; //ボディ画像
	std::vector<int> eye_animation;  //目画像
	int flash_count;    //点滅回数
	bool gate;          //ゲート・ワープの範囲内か(範囲内:true,範囲外:false)
	float mode_time;    //各状態の時間
	float anim_time;   //アニメーションカウント


public:
	EnemyBase();           //コンストラクタ
	virtual ~EnemyBase();  //デストラクタ

	virtual void Initialize() override;            //初期化処理
	void Update(float)override;                    //更新処理
	void Draw(const Vector2D&)const override;      //描画
	void Finalize()override;                       //終了処理
	void OnHitCollision(GameObjectBase*)override;  //Hit処理

	eEnemyState GetEnemyState() const; //敵の状態取得処理
	void SetPlayer(Player*);     //プレイヤーの情報を変数に入れる
	void SetName();

protected:
	virtual void Tuiseki(float);  //追跡状態

private:
	void Movement(float);  //移動処理
	void Nawabari(float);  //縄張り状態
	void Ijike(float);     //いじけ状態
	void Die(float);       //死
	void Wait(float);      //待機状態
	//const std::vector<eEnemyDirection>& Aster(std::vector<eEnemyDirection>&, std::vector<int>&, std::vector<int>&, const Vector2D&, eEnemyDirection);

	void SetDirection(Vector2D);  //移動方向変更処理
	void AnimControl(float);    //アニメーション処理
	void ChangeMode(float);     //状態の切り替え
};
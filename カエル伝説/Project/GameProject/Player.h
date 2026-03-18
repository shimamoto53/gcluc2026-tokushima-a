#pragma once
#include "CharaBase.h"
#include "Field.h"

class Player : public CharaBase
{
public:
	// コンストラクタ
	Player(const CVector3D& pos);
	// デストラクタ
	~Player();

	// 更新処理
	void Update() override;
	// 描画処理
	void Render() override;
	// スクロール
	void SetField(Field* f) { m_field = f; }


private:
	// 状態
	enum class EState
	{
		Idle,	// 待機状態
		Jump,	// ジャンプ中
		Attack,	// パンチ
		Kick,	// キック
		Death,	// 死亡
		Stun,	// スタン中
		
	};
	void ChangeState(EState state);

	// 移動処理の更新
	bool UpdateMove();

	// 待機時の更新処理
	void StateIdle();
	// ジャンプ中の更新処理
	void StateJump();
	// パンチの更新処理
	void StateAttack();
	// キックの更新処理
	void StateKick();
	// 死亡時の更新処理
	void StateDeath();
	// スタン中の処理
	void StateStun();
	
	bool m_isHit;
	int m_hitTimer;

	Field* m_field = nullptr;

	// アニメーションの種類
	enum class EAnimType
	{
		Idle,	// 待機
		Move,	// 移動
		Jump,	// ジャンプ
		Death,	// 死亡
		Attack,	// パンチ
		Kick,	// キック
		Stun,	// スタン

		Num,
	};

	EState m_state;
	int m_stateStep;

	static TexAnimData ANIM_DATA[];
	CImage* mp_image;	// プレイヤーの画像

	float m_moveSpeedY;	// Y軸（高さ）の移動速度
	float m_moveSpeedX; 
	float stunTimer = 0;
	float m_kickCoolTime = 0; // キックのクールタイム

	int blinkTimer = 0;   // 点滅用タイマー
	bool blink = true;    // 表示ON/OFF

	// ゲーム状態フラグ
	//extern bool g_isGameOver;
	//extern bool g_isGameClear;
};

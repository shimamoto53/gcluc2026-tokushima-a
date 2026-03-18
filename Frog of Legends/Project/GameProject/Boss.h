#pragma once
#include "EnemyBase.h"

// ボスの種類
enum class BossType
{
	Blue,
	Green,
	Yellow,

	Num
};

class Boss : public EnemyBase
{
public:

	// コンストラクタ
	Boss(BossType type, const CVector3D& pos);

	// デストラクタ
	virtual ~Boss();

	// ダメージ処理
	void TakeDamage(int damage);

	// 死亡処理
	void Death() override;

	// 更新処理
	void Update() override;

	// 描画処理
	void Render() override;

	CVector3D GetHitRange() const override;

	CVector3D GetHeadPos() const;

	CVector3D GetHeadHitRange() const;

private:

	// ボスの状態
	enum class EState
	{
		Idle,    // 待機
		Aim,     // 攻撃位置調整
		Attack,  // 突進
		Return,  // 元の位置へ戻る
		Death    // 死亡
	};

	// 状態変更
	void ChangeState(EState state);

	// 各状態の処理
	void StateIdle();
	void StateAim();
	void StateAttack();
	void StateReturn();
	void StateDeath();

	// 現在の状態
	EState m_state;

	// ステップカウンタ
	int m_stateStep;

	// 攻撃用座標
	float m_attackY;
	float m_headX;
	float m_headY;
	float m_startX;

	// 攻撃速度
	float m_attackSpeed;

	float m_bodyHitW;
	float m_bodyHitH;
	float m_bodyX;
	float m_bodyY;

	CVector3D m_hitRange;

	// アニメーション種類
	enum class EAnimType
	{
		Idle,
		Death,

		Num
	};

	// アニメーションデータ
	static TexAnimData ANIM_DATA[];

	// 画像
	CImage* mp_headImage;
	CImage* mp_bodyImage;

	// ボスタイプ
	BossType m_type;

	CVector3D m_headHitRange;
};
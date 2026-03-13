#include "Player.h"
#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Score.h"
#include "Field.h"

#define CHIP_SIZE 384		// 1コマのサイズ
#define CENTER_POS CVector2D(192.0f, 328.0f)	// 中心座標
#define MOVE_SPEED_X 5.0f	// 横方向の移動速度
#define MOVE_SPEED_Z 3.0f	// 奥方向の移動速度
#define JUMP_SPEED 15.0f	// ジャンプ速度
#define GRAVITY -1.0f		// 重力
#define ATTACK_INDEX 2		// 攻撃が発生するアニメーションの番号
#define ATTACK_RANGE CVector3D(300.0f, 10.0f, 50.0f)	// 攻撃範囲


#define SPAWN_PRANGE_MIN_X 100	// X軸の敵生成範囲の最小値
#define SPAWN_PRANGE_MAX_X (SCREEN_WIDTH - 100)	// X軸の敵生成範囲の最大値
#define SPAWN_PRANGE_MIN_Z -200	// Z軸の敵生成範囲の最小値
#define SPAWN_PRANGE_MAX_Z 100	// Z軸の敵生成範囲の最大値

// プレイヤーのアニメーションデータの前宣言
TexAnimData Player::ANIM_DATA[(int)EAnimType::Num] =
{
	// 待機アニメーション
	{
		new TexAnim[6]
		{
			{0, 6}, {1, 6}, {2, 6},
			{3, 6}, {4, 6}, {5, 6},
		},
		6
	},
	// 移動アニメーション
	{
		new TexAnim[6]
		{
			{6, 6}, {7, 6}, {8, 6},
			{9, 6}, {10, 6}, {11, 6},
		},
		6
	},
	// 死亡アニメーション
	{
		new TexAnim[3]
		{
			{12, 12},
			{13, 12},
			{14, 12},
		},
		3
	},
	// はたくアニメーション
	{
		new TexAnim[4]
		{
			{18, 6},
			{19, 6},
			{20, 6},
			{21, 6},
		},
		3
	},
	/*// キックアニメーション
	{
	new TexAnim[4]
		{
			{30, 6},
			{31, 6},
			{32, 6},
			{33, 6},
		},
		3
	},*/
	/*//　攻撃アニメーション
	{
		new TexAnim[4]
	{
		{24, 6},
		{25, 6},
		{26, 6},
		{27, 6},
	},
		4
	},*/
};


// コンストラクタ
Player::Player(const CVector3D& pos)
	: CharaBase(pos)
	, m_state(EState::Idle)
	, m_stateStep(0)
	, mp_image(nullptr)
{
	m_hp = 100;

	// プレイヤーの画像を読み込み
	mp_image = CImage::CreateImage
	(
		"player.png",	// 画像ファイルのパス
		ANIM_DATA,		// アニメーションのデータ
		CHIP_SIZE, CHIP_SIZE	// 1コマの幅と高さ
	);
	mp_image->ChangeAnimation((int)EAnimType::Idle);
	mp_image->SetCenter(CENTER_POS);
}

// デストラクタ
Player::~Player()
{
	// 画像データを削除
	delete mp_image;
}

// 現在の状態を切り替え
void Player::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// 移動処理の更新
bool Player::UpdateMove()
{
	bool isMove = false;
	
		// 左キーを押している間
		if (HOLD(CInput::eLeft))
		{
			// 左方向へ移動
			m_pos.x -= MOVE_SPEED_X;
			mp_image->SetFlipH(true);
			isMove = true;
		}
		// 右キーを押している間
		else if (HOLD(CInput::eRight))
		{
			// 右方向へ移動
			m_pos.x += MOVE_SPEED_X;
			mp_image->SetFlipH(false);
			isMove = true;
		}
		// 上キーを押している間
		if (HOLD(CInput::eUp))
		{
			// 奥方向へ移動
			m_pos.z -= MOVE_SPEED_Z;
			isMove = true;
		}
		// 下キーを押している間
		else if (HOLD(CInput::eDown))
		{
			// 手前方向へ移動
			m_pos.z += MOVE_SPEED_Z;
			isMove = true;
		}
	

		if (m_pos.x < SPAWN_PRANGE_MIN_X) m_pos.x = SPAWN_PRANGE_MIN_X;
		if (m_pos.x > SPAWN_PRANGE_MAX_X) m_pos.x = SPAWN_PRANGE_MAX_X;
		if (m_pos.z < SPAWN_PRANGE_MIN_Z) m_pos.z = SPAWN_PRANGE_MIN_Z;
		if (m_pos.z > SPAWN_PRANGE_MAX_Z) m_pos.z = SPAWN_PRANGE_MAX_Z;
		
	return isMove;
}

// 待機時の更新処理
void Player::StateIdle()
{
	// 移動処理
	bool isMove = UpdateMove();
	float scrollSpeed = m_field->GetScrollSpeed();
	if (scrollSpeed != 0.0f)
	{
		m_pos.x -= scrollSpeed;
	}

	// 移動状態に合わせて、アニメーションを切り替え
	EAnimType anim = isMove ? EAnimType::Move : EAnimType::Idle;
	mp_image->ChangeAnimation((int)anim);

	// [J]キーと[SPACE]キーでキックへ移行
	if (HOLD(CInput::eButton1) && HOLD(CInput::eButton2))
	{
		ChangeState(EState::Kick);
	}
	// [SPACE]キーでジャンプ状態へ移行
	else if (PUSH(CInput::eButton1))
	{
		ChangeState(EState::Jump);
	}
	// [J]キーで攻撃状態へ移行
	else if (PUSH(CInput::eButton2))
	{
		ChangeState(EState::Attack);
	}
	// [C]キーでスタン状態へ移行(デバック用)
	else if (PUSH(CInput::eButton3))
	{
		ChangeState(EState::Stun);
		stunTimer = 50.0f;
	}
}

// 攻撃中の更新処理
void Player::StateKick()
{
	// ステップごとに処理を切り替え
	switch (m_stateStep)
	{
		// ステップ0：キックアニメーションに切り替え
	case 0:
		mp_image->ChangeAnimation((int)EAnimType::Attack, false);
		m_stateStep++;
		break;
		// ステップ1：攻撃判定
	case 1:
		// キックのアニメーションが攻撃タイミングまで進めば
		if (mp_image->GetIndex() >= ATTACK_INDEX)
		{
			// 一番近い敵にダメージを与える
			EnemyBase* enemy = EnemyManager::Instance()->GetNearEnemy(m_pos, ATTACK_RANGE);
			if (enemy != nullptr)
			{
				int score = Score::Get();

				// スコアが50以上ならキック追加
				if (score >= 50)
				{
					enemy->TakeDamage(100);
				}
				m_stateStep++;
			}
		}
		break;
		// ステップ2：アニメーション終了待ち
	case 2:
		// キックのアニメーションが終了したら、待機状態へ移行
		if (mp_image->CheckAnimationEnd())
		{
			ChangeState(EState::Idle);
		}
		break;
	}
}

// ジャンプ中の更新処理
void Player::StateJump()
{
	// ステップごとに処理を切り替え
	switch(m_stateStep)
	{
		// ステップ0：ジャンプ開始
		case 0:
			// Y軸（高さ）の移動速度にジャンプを速度を設定し、
			// 接地状態を解除する
			m_moveSpeedY = JUMP_SPEED;
			m_isGrounded = false;
			m_stateStep++;
			break;
		// ステップ1：ジャンプ終了
		case 1:
			// 接地したら、待機状態へ移行
			if (m_isGrounded)
			{
				ChangeState(EState::Idle);
			}
			break;
	}

	// 移動処理
	bool isMove = UpdateMove();
	mp_image->ChangeAnimation((int)EAnimType::Idle);
}

// 攻撃中の更新処理
void Player::StateAttack()
{
	// ステップごとに処理を切り替え
	switch (m_stateStep)
	{
		// ステップ0：攻撃アニメーションに切り替え
		case 0:
			mp_image->ChangeAnimation((int)EAnimType::Attack, false);
			m_stateStep++;
			break;
			// ステップ1：攻撃判定
		case 1:
			// 攻撃アニメーションが攻撃タイミングまで進めば
			if (mp_image->GetIndex() >= ATTACK_INDEX)
			{
				// 一番近い敵にダメージを与える
				EnemyBase* enemy = EnemyManager::Instance()->GetNearEnemy(m_pos, ATTACK_RANGE);
				if (enemy != nullptr)
				{
					int score = Score::Get();

					// スコアが50未満ならパンチのみ
						enemy->TakeDamage(50);
				}
				m_stateStep++;
			}
			break;
			// ステップ2：アニメーション終了待ち
		case 2:
			// 攻撃アニメーションが終了したら、待機状態へ移行
			if (mp_image->CheckAnimationEnd())
			{
				ChangeState(EState::Idle);
			}
			break;
	}
}

// スタン中の処理
void Player::StateStun()
{
	mp_image->ChangeAnimation((int)EAnimType::Idle);

	if (stunTimer > 0)
	{
		stunTimer-=1.0f;
	}
	else
	{
		stunTimer = 0;
		ChangeState(EState::Idle); // スタン終了
	}
}

// 死亡時の更新処理
void Player::StateDeath()
{
}

// 更新処理
void Player::Update()
{
	/*
	EnemyBase* enemy = EnemyManager::Instance()->GetNearEnemy(m_pos, CVector3D(50, 50, 50));
	if (enemy != nullptr)
	{
		ChangeState(EState::Stun);
		stunTimer = 50.0f;
	}*/
	
	// 現在の状態に合わせて、処理を切り替える
	switch (m_state)
	{
	case EState::Idle:		StateIdle();	break;
	case EState::Jump:		StateJump();	break;
	case EState::Attack:	StateAttack();	break;
	case EState::Kick:		StateKick();	break;
	case EState::Death:		StateDeath();	break;
	case EState::Stun:		StateStun();	break;
	}

	// Y軸（高さ）の移動を座標に反映
	m_pos.y += m_moveSpeedY;
	m_moveSpeedY += GRAVITY;	// Y軸の移動速度に重力を加算
	// 地面より下にいくと
	if (m_pos.y <= 0.0f)
	{
		// 地面の座標へ戻す
		m_pos.y = 0.0f;
		m_moveSpeedY = 0.0f;
		m_isGrounded = true;
	}

	// イメージに座標を設定して、アニメーションを更新
	mp_image->SetPos(CalcScreenPos());
	mp_image->UpdateAnimation();

	DebugPrint::Print("プレイヤー位置：%.2f, %.2f, %.2f", m_pos.x, m_pos.y, m_pos.z);
	DebugPrint::Print("Score:%d", Score::Get());
}

// 描画処理
void Player::Render()
{
	mp_image->Draw();
}

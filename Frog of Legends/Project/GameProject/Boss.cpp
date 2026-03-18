#include "Boss.h"
#include "Score.h"
#include "EnemyManager.h"
#include "GameClearTask.h"
#include "Field.h"
#include "Player.h"
#include "TaskManager.h"
#include "Task.h"
#include "GameOverTask.h"

extern bool g_isGameClear;
extern bool g_isGameOver;
extern Field* g_field;

#define CHIP_SIZE 512
#define CENTER_POS CVector2D(100.0f,300.0f)
#define ENEMY_SPEED 5.0f

#define BOSSATTACK_AREA_MIN_Y -100//200
#define BOSSATTACK_AREA_MAX_Y 350//(SCREEN_HEIGHT - 200)

// ボスのアニメーションデータ
TexAnimData Boss::ANIM_DATA[(int)EAnimType::Num] =
{
	{
		new TexAnim[4]
		{
			{ 0, 6}, { 1, 6},
			{ 2, 6}, { 3, 6},
		},
		4
	},
	{
		new TexAnim[5]
		{
			{5, 6}, {6, 6}, {7, 6},
			{8, 6}, {9, 6},
		},
		5
	},
};

// コンストラクタ
Boss::Boss(BossType type, const CVector3D& pos)
	: EnemyBase(pos)
	, mp_headImage(nullptr)
	, mp_bodyImage(nullptr)
	, m_type(type)
{
	m_hp = 6000;

	mp_headImage = CImage::CreateImage(
		"Boss_neck.png",
		ANIM_DATA,
		200,200
	);

	mp_bodyImage = CImage::CreateImage("Boss.png");

	mp_headImage->SetCenter(CENTER_POS);
	mp_bodyImage->SetCenter(CVector2D(0, 0));

	mp_headImage->SetFlipH(false);
	mp_bodyImage->SetFlipH(false);

	m_bodyHitW = 350;
	m_bodyHitH = 300;

	m_startX = m_pos.x - 230;
	m_headX = m_startX;
	m_headY = 0;

	m_attackSpeed = 15.0f;

	m_state = EState::Idle;
	m_stateStep = 0;
	mp_headImage->ChangeAnimation((int)EAnimType::Idle);
	m_hitRange = CVector3D(200.0f, 0.0f, 400.0f);
	m_headHitRange = CVector3D(100.0f, 100.0f, 100.0f);
}

// デストラクタ
Boss::~Boss()
{
	delete mp_headImage;
	delete mp_bodyImage;
}

// ダメージ処理
void Boss::TakeDamage(int damage)
{
	m_hp -= damage;

	if (m_hp <= 0)
	{
		Death();
	}
}

void Boss::Death()
{
	g_isGameClear = true;

	// 他の敵削除
	EnemyManager::Instance()->KillAllEnemies();

	// フィールド削除
	delete g_field;
	g_field = nullptr;

	// クリア画面
	new GameClearTask();

	// 自分削除
	Kill();
}

// 状態変更
void Boss::ChangeState(EState state)
{
	if (m_state == state) return;

	m_state = state;
	m_stateStep = 0;
}

// 待機
void Boss::StateIdle()
{
	mp_headImage->ChangeAnimation((int)EAnimType::Idle);
	mp_bodyImage->ChangeAnimation((int)EAnimType::Idle);

	if (++m_stateStep > 120)
	{
		ChangeState(EState::Aim);
	}
}

// 攻撃位置決定
void Boss::StateAim()
{
	switch (m_stateStep)
	{
	case 0:

		m_attackY = BOSSATTACK_AREA_MIN_Y +
			rand() % (BOSSATTACK_AREA_MAX_Y - BOSSATTACK_AREA_MIN_Y);

		m_stateStep++;
		break;

	case 1:

		if (m_headY < m_attackY)
			m_headY += 5;

		if (m_headY > m_attackY)
			m_headY -= 5;

		if (abs(m_headY - m_attackY) < 10)
		{
			ChangeState(EState::Attack);
		}

		break;
	}
}

// 攻撃
void Boss::StateAttack()
{
	m_headX -= m_attackSpeed;

	if (m_headX < 5)
	{
		ChangeState(EState::Return);
	}
}

// 戻る
void Boss::StateReturn()
{
	m_headX += m_attackSpeed;

	if (m_headX >= m_startX)
	{
		m_headX = m_startX;
		ChangeState(EState::Idle);
	}
}

// 死亡
void Boss::StateDeath()
{
	switch (m_stateStep)
	{
	case 0:

		mp_headImage->ChangeAnimation((int)EAnimType::Death, false);
		mp_bodyImage->ChangeAnimation((int)EAnimType::Death, false);

		m_stateStep++;
		break;

	case 1:

		if (mp_headImage->CheckAnimationEnd())
		{
			g_isGameClear = true;

			EnemyManager::Instance()->KillAllEnemies();

			delete g_field;
			g_field = nullptr;

			new GameClearTask();

			Kill();
		}

		break;
	}
}

CVector3D Boss::GetHitRange() const
{
	return m_hitRange;
}

CVector3D Boss::GetHeadPos() const
{
	return CVector3D(m_headX, m_pos.y, m_headY);
}

CVector3D Boss::GetHeadHitRange() const
{
	return m_headHitRange;
}

// 更新処理
void Boss::Update()
{
	if (m_stateStep == 0)
	{
		mp_headImage->ChangeAnimation((int)EAnimType::Idle);
	}

	if (g_isGameClear)
	{
		Kill();
		return;
	}

	if (g_isGameOver)
	{
		Kill();
		return;
	}

	switch (m_state)
	{
	case EState::Idle:   StateIdle();   break;
	case EState::Aim:    StateAim();    break;
	case EState::Attack: StateAttack(); break;
	case EState::Return: StateReturn(); break;
	case EState::Death:  StateDeath();  break;
	}
	float bodyX = SCREEN_WIDTH - 620;
	float bodyY = SCREEN_HEIGHT / 2.25;

	mp_bodyImage->SetPos(bodyX,bodyY);
	//float screenY = SCREEN_HEIGHT / 2 - m_headY;
	//mp_headImage->SetPos(m_headX, m_headY);
	/*
	m_pos.x = m_headX;
	m_pos.z = m_headY; */

	//mp_headImage->SetPos(CalcScreenPos());
	/*CVector3D old = m_pos;

	// ★一時的に頭座標入れる
	m_pos.x = m_headX;   
	m_pos.z = m_headY;   

	mp_headImage->SetPos(CalcScreenPos());

	// ★戻す（重要）
	m_pos = old;  */
	
	CVector3D old = m_pos;              // ★元の座標保存

	m_pos.x = m_headX;                  // ★頭のX
	m_pos.z = m_headY;                  // ★頭のZ（プレイヤーと同じ扱い）

	mp_headImage->SetPos(CalcScreenPos()); // ★プレイヤーと同じ変換

	m_pos = old;                        // ★元に戻す（超重要）

	mp_headImage->UpdateAnimation();
	mp_bodyImage->UpdateAnimation();
}

// 描画
void Boss::Render()
{
	if (g_isGameClear) return;
	float screenY = SCREEN_HEIGHT / 2 - m_headY;
	mp_bodyImage->Draw();
	mp_headImage->Draw();
}
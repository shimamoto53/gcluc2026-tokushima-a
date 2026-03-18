#include "EnemyManager.h"
#include "EnemyBase.h"
#include "Slime.h"
#include "Boss.h"
#include "Timer.h"

extern bool g_isGameOver;
extern bool g_isGameClear;

#define SPAWN_COUNT 90			// 敵生成数
#define SPAWN_INTERVAL 1.5f		// 敵を生成する間隔時間
#define SPAWN_RANGE_MIN_X (SCREEN_WIDTH - 150)	// X軸の敵生成範囲の最小値
#define SPAWN_RANGE_MAX_X (SCREEN_WIDTH - 50)	// X軸の敵生成範囲の最大値
#define SPAWN_RANGE_MIN_Z -200	// Z軸の敵生成範囲の最小値
#define SPAWN_RANGE_MAX_Z 100	// Z軸の敵生成範囲の最大値

EnemyManager* EnemyManager::ms_instance = nullptr;

// コンストラクタ
EnemyManager::EnemyManager()
	: Task((int)ETaskPrio::Manager)
	, m_elapsedTime(0.0f)
	, m_isBossSpawned(false)
{
}

// デストラクタ
EnemyManager::~EnemyManager()
{
	if (ms_instance == this)
	{
		ms_instance = nullptr;
	}
}

// インスタンス取得
EnemyManager* EnemyManager::Instance()
{
	// インスタンスがなければ、生成
	if (ms_instance == nullptr)
	{
		ms_instance = new EnemyManager();
	}
	return ms_instance;
}

// 敵をリストに追加
void EnemyManager::Add(EnemyBase* enemy)
{
	m_enemies.push_back(enemy);
}

// 敵をリストから取り除く
void EnemyManager::Remove(EnemyBase* enemy)
{
	auto itr = std::remove(m_enemies.begin(), m_enemies.end(), enemy);
	m_enemies.erase(itr, m_enemies.end());
}

// 指定した位置から一番近い敵を取得
EnemyBase* EnemyManager::GetNearEnemy(const CVector3D& pos, const CVector3D& range)
{
	// 生成済みの全ての敵の中から一番近い敵を探す
	EnemyBase* nearEnemy = nullptr;
	float nearDist = 0.0f;
	/*
	for (EnemyBase* enemy : m_enemies)
	{
		// 各軸の距離を求めて、範囲外であればスルー
		CVector3D enemyPos = enemy->GetPos();
		if (abs(pos.x - enemyPos.x) > range.x) continue;
		if (abs(pos.y - enemyPos.y) > range.y) continue;
		if (abs(pos.z - enemyPos.z) > range.z) continue;

		

		Boss* boss = dynamic_cast<Boss*>(enemy);
		if (boss)
		{
			CVector3D headPos = boss->GetHeadPos();
			CVector3D headRange = boss->GetHeadHitRange();

			if (abs(pos.x - headPos.x) <= (range.x + headRange.x) &&
				abs(pos.y - headPos.y) <= (range.y + headRange.y) &&
				abs(pos.z - headPos.z) <= (range.z + headRange.z))
			{
				return enemy; // 頭にヒット
			}
		}

		CVector3D enemyRange = enemy->GetHitRange();

		if (abs(pos.x - enemyPos.x) > (range.x + enemyRange.x)) continue;
		if (abs(pos.y - enemyPos.y) > (range.y + enemyRange.y)) continue;
		if (abs(pos.z - enemyPos.z) > (range.z + enemyRange.z)) continue;

		// 現在の一番近い敵より近い場合は、一番近い敵に設定
		float dist = (pos - enemyPos).Length();
		if (nearEnemy == nullptr || dist < nearDist)
		{
			nearEnemy = enemy;
			nearDist = dist;
		}
	}*/
	for (EnemyBase* enemy : m_enemies)
	{
		Boss* boss = dynamic_cast<Boss*>(enemy);

		// ★先に頭判定
		if (boss)
		{
			CVector3D headPos = boss->GetHeadPos();
			CVector3D headRange = boss->GetHeadHitRange();

			if (abs(pos.x - headPos.x) <= (range.x + headRange.x) &&
				abs(pos.y - headPos.y) <= (range.y + headRange.y) &&
				abs(pos.z - headPos.z) <= (range.z + headRange.z))
			{
				return enemy; // ★ここで即ヒット
			}
		}

		// ★その後にボディ判定
		CVector3D enemyPos = enemy->GetPos();
		CVector3D enemyRange = enemy->GetHitRange();

		if (abs(pos.x - enemyPos.x) > (range.x + enemyRange.x)) continue;
		if (abs(pos.y - enemyPos.y) > (range.y + enemyRange.y)) continue;
		if (abs(pos.z - enemyPos.z) > (range.z + enemyRange.z)) continue;

		float dist = (pos - enemyPos).Length();
		if (nearEnemy == nullptr || dist < nearDist)
		{
			nearEnemy = enemy;
			nearDist = dist;
		}
	}
	return nearEnemy;
}

// 更新
void EnemyManager::Update()
{
	// 残り時間が30秒以下でボス出現
	if (!m_isBossSpawned && Timer::GetRemaining() <= 0)
	{
		KillAllEnemies();

		CVector3D pos;
		pos.x = SCREEN_WIDTH - 100;
		pos.y = 0;
		pos.z = 0;

		new Boss(BossType::Blue, pos);

		m_isBossSpawned = true;
	}

	if (g_isGameOver || g_isGameClear)
		return;

	// 現在の敵の数が、敵生成数を超えてなければ、
	if (!m_isBossSpawned && m_enemies.size() < SPAWN_COUNT) 
	{
		// 経過時間が生成間隔の時間を超えたら
		if (m_elapsedTime >= SPAWN_INTERVAL)
		{
			// スライムの種類をランダムで決定
			SlimeType type = (SlimeType)Utility::Rand(0, (int)SlimeType::Num - 1);

			// スライムの位置をランダムで決定
			CVector3D pos;
			pos.x = Utility::Rand(SPAWN_RANGE_MIN_X, SPAWN_RANGE_MAX_X);
			pos.y = 0.0f;
			pos.z = Utility::Rand(SPAWN_RANGE_MIN_Z, SPAWN_RANGE_MAX_Z);

			// スライムを生成
			new Slime(type, pos);

			m_elapsedTime -= SPAWN_INTERVAL;
		}

		// 経過時間を加算
		m_elapsedTime += CFPS::GetDeltaTime();
	}
	// 敵生成数に達している状態
	else
	{
		m_elapsedTime = 0.0f;
	}
}

void EnemyManager::Destroy()
{
	if (ms_instance != nullptr)
	{
		delete ms_instance;
		ms_instance = nullptr;
	}
}

void EnemyManager::KillAllEnemies()
{
	for (auto enemy : m_enemies)
	{
		enemy->Kill();
	}

	m_enemies.clear();
}

void EnemyManager::Reset()
{
	m_elapsedTime = 0.0f;
	m_isBossSpawned = false;
}
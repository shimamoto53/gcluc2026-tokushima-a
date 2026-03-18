#pragma once
#include "Task.h"

class EnemyBase;

// 敵管理クラス
class EnemyManager : public Task
{
public:
    // インスタンス取得
    static EnemyManager* Instance();

    static void Destroy();//追加

    void KillAllEnemies();//追加

    // 敵をリストに追加
    void Add(EnemyBase* enemy);
    // 敵をリストから取り除く
    void Remove(EnemyBase* enemy);

    // 指定した位置から一番近い敵を取得
    EnemyBase* GetNearEnemy(const CVector3D& pos, const CVector3D& range);

    // 更新
    void Update() override;

    void Reset();
    
private:
    // コンストラクタ
    EnemyManager();
    // デストラクタ
    ~EnemyManager();

    // インスタンス
    static EnemyManager* ms_instance;
    // 生成済みのエネミーのリスト
    std::vector<EnemyBase*> m_enemies;

    float m_elapsedTime;    // 経過時間計測用

    bool m_isBossSpawned;
};
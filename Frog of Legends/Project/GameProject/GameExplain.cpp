#include "GameExplain.h"
#include "DebugPrint.h"
#include "Field.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Timer.h"
#include "TitleTask.h"

extern Field* g_field;
extern Player* g_player;

GameExplainTask::GameExplainTask()
    : Task(0)
{
    mp_explain = CImage::CreateImage("set.png");
}

GameExplainTask::~GameExplainTask()
{
    delete mp_explain;
}

void GameExplainTask::Update()
{
    // Zキー → ゲームスタート
    if (PUSH(CInput::eButton7))
    {
        // 敵（ボス含む）削除
        EnemyManager::Destroy();

        // フィールド削除
        if (g_field)
        {
            delete g_field;
            g_field = nullptr;
        }

        // プレイヤー削除
        if (g_player)
        {
            g_player->Kill();
            g_player = nullptr;
        }

        g_field = new Field();

        g_player = new Player(
            CVector3D(SCREEN_WIDTH * 0.2f, 0.0f, 0.0f));

        g_player->SetField(g_field);

        EnemyManager::Instance();

        Timer::Start();

        Kill();
    }

    // Bキー → タイトル
    if (PUSH(CInput::eButton6))
    {
        new TitleTask();
        Kill();
    }
}

void GameExplainTask::Render()
{
    mp_explain->SetPos(0, 0);
    mp_explain->Draw();
}
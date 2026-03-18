#include "GameClearTask.h"
#include "DebugPrint.h"
#include "Field.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Timer.h"
#include "TitleTask.h"
#include "Score.h"

extern Field* g_field;
extern Player* g_player;

extern bool g_isGameOver;   // ←追加
extern bool g_isGameClear;  // ←追加

GameClearTask::GameClearTask()
    : Task(0)
{
    mp_clear = CImage::CreateImage("Clear.png");

    // 敵（ボス含む）削除
    EnemyManager::Instance()->KillAllEnemies();  // ←追加
    EnemyManager::Destroy();

    mp_restart = CImage::CreateImage("gamestart.png");
    //mp_titleBtn = CImage::CreateImage("exitgame.png");
    mp_exit = CImage::CreateImage("exitgame.png");

    mp_marker = CImage::CreateImage("テッポウウオ.png");

    m_select = 0;

    // 残り時間
    int elapsed = Timer::GetElapsed();
    m_clearTime = 60 - elapsed;
    if (m_clearTime < 0) m_clearTime = 0;
}

GameClearTask::~GameClearTask()
{
    delete mp_clear;
    delete mp_restart;
    delete mp_exit;
    delete mp_marker;
}

void GameClearTask::Update()
{
    SOUND("bgm")->Stop();
    // 上
    if (PUSH(CInput::eUp))
    {
        m_select--;

        if (m_select < 0)
            m_select = 1;
    }

    // 下
    if (PUSH(CInput::eDown))
    {
        m_select++;

        if (m_select > 1)
            m_select = 0;
    }

    // 決定
    if (PUSH(CInput::eButton10))
    {
        switch (m_select)
        {
        case 0: // ゲーム再開

            // 敵マネージャー完全削除
          //  EnemyManager::Destroy();

            // フラグリセット
            g_isGameOver = false;
            g_isGameClear = false;

            // 古いプレイヤー削除
            if (g_player)
            {
                g_player->Kill();
                g_player = nullptr;
            }

            // 古いフィールド削除
            if (g_field)
            {
                delete g_field;
                g_field = nullptr;
            }

            // フィールド生成
            g_field = new Field();

            // プレイヤー生成
            g_player = new Player(
                CVector3D(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f));

            g_player->SetField(g_field);            
            
            // 敵マネージャー生成
            EnemyManager::Instance();
            EnemyManager::Instance()->Reset();

            // タイマーリセット
            Timer::Start();

            Kill();

            break;

        case 1: // ゲーム終了
            exit(0);
            break;
        }
    }
}

void GameClearTask::Render()
{
    mp_clear->SetPos(0, 0);
    mp_clear->Draw();

    // 時間表示
    int min = m_clearTime / 60;
    int sec = m_clearTime % 60;

    DebugPrint::Print("Clear Time %d:%02d", min, sec);

    int x = 700;
    int y = 450;
    int space = 120;

    // ボタン
    mp_restart->SetPos(x, y);
    mp_restart->Draw();

    //mp_titleBtn->SetPos(x, y + space);
    //mp_titleBtn->Draw();

    mp_exit->SetPos(x, y + space);
    mp_exit->Draw();

    // マーカー
    int markerX = x - 120;
    int markerY = y + space * m_select;

    mp_marker->SetPos(markerX, markerY);
    mp_marker->Draw();
   // CREATE_FONT_F("score", "C:\\Windows\\Fonts\\msgothic.ttc", 80);
   /* FONT("score")->Draw(850, 450, 1, 1, 1, "スコア");
    FONT("score")->Draw(910, 560, 1, 1, 1, "%d", Score::Get());*/

    int time = Timer::GetResult();

   

    FONT("timer")->Draw(800, 400, 1, 1, 1, "TIME %d:%02d", min, sec);
}
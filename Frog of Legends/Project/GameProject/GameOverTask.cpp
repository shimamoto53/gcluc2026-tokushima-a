#include "GameOverTask.h"
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

GameOverTask::GameOverTask()
    : Task(0)
{
    mp_over = CImage::CreateImage("Over.png");

    // ボタン
    mp_restart = CImage::CreateImage("gamestart.png");
    mp_exit = CImage::CreateImage("exitgame.png");

    // マーカー
    mp_marker = CImage::CreateImage("テッポウウオ.png");

    m_select = 0;

    // 敵生成停止
   // EnemyManager::Destroy();
    EnemyManager::Instance()->KillAllEnemies();

    g_isGame = false;
}

GameOverTask::~GameOverTask()
{
    delete mp_over;
    delete mp_restart;
  //  delete mp_titleBtn;
    delete mp_exit;
    delete mp_marker;
}

void GameOverTask::Update()
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

            // フラグリセット
            g_isGameOver = false;
            g_isGameClear = false;

            // フィールド生成
            g_field = new Field();

            // プレイヤー生成
            g_player = new Player(
                CVector3D(SCREEN_WIDTH * 0.2f, 0.0f, 0.0f));

            g_player->SetField(g_field);

            // 敵マネージャー生成
            EnemyManager::Instance();
            EnemyManager::Instance()->Reset();

            Score::Reset();

            // タイマーリセット
            Timer::Start();
            g_isGame = true;

            Kill();
            break;

        case 1: // 終了

            exit(0);

            break;
        }
    }
}

void GameOverTask::Render()
{
    mp_over->SetPos(0, 0);
    mp_over->Draw();

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
}
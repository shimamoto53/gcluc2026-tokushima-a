#include "TitleTask.h"
#include "DebugPrint.h"
#include "Field.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Timer.h"
#include "GameExplain.h"
#include "Score.h"

static bool isBgmStart = false;
extern Field* g_field;
extern Player* g_player;

TitleTask::TitleTask()
    :Task(0)
{
    mp_title = CImage::CreateImage("Title.png");

    mp_start = CImage::CreateImage("Game_Start.png");
    mp_explain = CImage::CreateImage("Game_Explain.png");
    mp_exit = CImage::CreateImage("Game_Exit.png");

    mp_marker = CImage::CreateImage("SmallMarker.png");

    m_select = 0;
}

TitleTask::~TitleTask()
{
    delete mp_title;
    delete mp_start;
    delete mp_explain;
    delete mp_exit;
    delete mp_marker;
}

void TitleTask::Update()
{
    // 上
    if (PUSH(CInput::eUp))
    {
        m_select--;

        if (m_select < 0)
            m_select = 2;
    }

    // 下
    if (PUSH(CInput::eDown))
    {
        m_select++;

        if (m_select > 2)
            m_select = 0;
    }

    // 決定
    if (PUSH(CInput::eButton10))
    {
        SOUND("select")->Play();
        switch (m_select)
        {
        case 0: // Game Start
        {
            Score::Reset();

            Timer::Start();   // タイマー開始
            g_isGame = true;

            if (!isBgmStart)
            {
                SOUND("bgm")->Volume(0.2f);
                SOUND("bgm")->Play(true);
                isBgmStart = true;
            }

            g_field = new Field();

            g_player = new Player(
                CVector3D(SCREEN_WIDTH * 0.2f, 0.0f, 0.0f));

            g_player->SetField(g_field);

            EnemyManager::Instance();

            Kill();

        }
            break;

        case 1: // Explain
            new GameExplainTask();
            Kill();
            break;

        case 2: // Exit
            exit(0);
            break;
        }
    }
}

void TitleTask::Render()
{
    // タイトル
    mp_title->SetPos(0, 0);
    mp_title->Draw();

    int x = 600;
    int y = 550;
    int space = 120;

    // Startボタン
    mp_start->SetPos(x, y);
    mp_start->Draw();

    mp_explain->SetPos(x, y + space);
    mp_explain->Draw();

    mp_exit->SetPos(x, y + space * 2);
    mp_exit->Draw();

    // マーカー
    int markerX = x - 100;
    int markerY = y + space * m_select;

    mp_marker->SetPos(markerX, markerY);
    mp_marker->Draw();
}
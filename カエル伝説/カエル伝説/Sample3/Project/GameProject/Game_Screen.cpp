//ヘッダーファイル
#include  "game_screen.h"

//コンストラクタ
CGameScreen::CGameScreen()
{
	TaskManager::Instance();
	m_State = GAME_SCREEN;

}
//デストラクタ
CGameScreen::~CGameScreen()
{
}

//更新処理
void CGameScreen::Update()
{
	static bool isBgmStart = false;

	if (!isBgmStart)
	{
		SOUND("bgm")->Volume(0.2f);
		SOUND("bgm")->Play(true);
		isBgmStart = true;
	}
	//タスクリストに登録されたタスクを全て更新
	TaskManager::Instance()->Update();
	m_Timer++;

	if (PUSH(CInput::eButton4))
	{
		m_State = GAMEBOSS_SCREEN;
	}

}

//描画処理
void CGameScreen::Draw() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	TaskManager::Instance()->Render();

	// タイトル画像表示
	if (m_Image)
	{
		m_Image->Draw();
	}

	DebugPrint::Print("Game Screen Hit V key to GameBoss Screen");
}

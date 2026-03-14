//ヘッダーファイル
#include "gameboss_screen.h"

//コンストラクタ
CGameBossScreen::CGameBossScreen()
{
	m_State = GAMEBOSS_SCREEN;
	//m_Image = CImage::CreateImage("gamen.png");
}

//デストラクタ
CGameBossScreen::~CGameBossScreen() {}

//実行処理
void CGameBossScreen::Update()
{
	m_Timer++;

	if (PUSH(CInput::eButton4))
	{
		m_State = GAMECLEAR_SCREEN;
	}
	if (PUSH(CInput::eButton5))
	{
		m_State = GAMEOVER_SCREEN;
	}
}

//描画処理
void CGameBossScreen::Draw() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// タイトル画像表示
	if (m_Image)
	{
		m_Image->Draw();
	}
	DebugPrint::Print("GameBoss Screen Hit B key to GameOver  V key to GameClear");
}
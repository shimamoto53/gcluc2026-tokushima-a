//ヘッダーファイル
#include "GameTitle_Screen.h"

//コンストラクタ
CTitleScreen::CTitleScreen()
{
	m_State = TITLE_SCREEN;
	m_Timer = 0;

	//m_Image = CImage::CreateImage("gamen.png");
}

//デストラクタ
CTitleScreen::~CTitleScreen()
{
}

//実行処理
void CTitleScreen::Update()
{
	m_Timer++;

	if (m_Timer > 30 && PUSH(CInput::eButton4))
	{
		SOUND("select")->Play();
		m_State = GAME_SCREEN;
	}
}

void CTitleScreen::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// タイトル画像表示
	if (m_Image)
	{
		m_Image->Draw();
	}

	DebugPrint::Print("Title Screen Hit V key to Game Screen");
}
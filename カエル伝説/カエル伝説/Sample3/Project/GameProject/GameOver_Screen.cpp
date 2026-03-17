#include"GameOver_Screen.h"

//コンストラクタ
CGameOverScreen::CGameOverScreen()
{
	m_State = GAMEOVER_SCREEN;
	m_Timer = 0;

	//m_Image = CImage::CreateImage("gamen.png");
}

//デストラクタ
CGameOverScreen::~CGameOverScreen()
{
}

//実行処理
void CGameOverScreen::Update()
{
	SOUND("bgm")->Stop();
	m_Timer++;

	if (m_Timer > 30 && PUSH(CInput::eButton4))
	{
		m_State = TITLE_SCREEN;
	}
}

//描画
void CGameOverScreen::Draw() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// タイトル画像表示
	if (m_Image)
	{
		m_Image->Draw();
	}
	DebugPrint::Print("GameOver Screen Hit V key to Title Screen");
}
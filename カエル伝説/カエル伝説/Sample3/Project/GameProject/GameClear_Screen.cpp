//ヘッダーファイル
#include"GameClear_Screen.h"
#include "Score.h"

//コンストラクタ
CGameClearScreen::CGameClearScreen()
{
	m_State = GAMECLEAR_SCREEN;
	m_Timer = 0;

	//m_Image = CImage::CreateImage("gamen.png");
}

//デストラクタ
CGameClearScreen::~CGameClearScreen()
{
}

//実行処理
void CGameClearScreen::Update()
{
	m_Timer++;

	if (m_Timer > 30 && PUSH(CInput::eButton4))
	{
		m_State = TITLE_SCREEN;
	}
}

//描画
void CGameClearScreen::Draw() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// タイトル画像表示
	if (m_Image)
	{
		m_Image->Draw();
	}
	CREATE_FONT_F("score", "C:\\Windows\\Fonts\\msgothic.ttc", 80);
	FONT("score")->Draw(850, 450, 1, 1, 1, "スコア");
	FONT("score")->Draw(910, 560, 1, 1, 1, "%d", Score::Get());
	DebugPrint::Print("GameClear Screen Hit V key to Title Screen");
}
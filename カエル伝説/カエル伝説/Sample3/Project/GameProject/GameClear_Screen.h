#pragma once

//ヘッダーファイル
#include "Global.h"
#include "screen.h"

//ゲームクリアスクリーンクラス
class CGameClearScreen : public CScreen
{
private:
	int m_Timer = 0;
	CImage* m_Image = 0;
	int m_lasttime;
public:
	CGameClearScreen();
	~CGameClearScreen();
	void Update();
	void Draw() const;
};
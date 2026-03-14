#pragma once

//ヘッダーファイル
#include "Global.h"
#include "screen.h"

//ゲームオーバースクリーンクラス
class CGameOverScreen : public CScreen
{
private:
	int m_Timer = 0;
	CImage* m_Image = 0;
	int m_lasttime;
public:
	CGameOverScreen();
	~CGameOverScreen();
	void Update();
	void Draw() const;
};
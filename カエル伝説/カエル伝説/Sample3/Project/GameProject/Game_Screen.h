#pragma once

//ヘッダーファイル
#include"Global.h"
#include "TaskManager.h"
#include"screen.h"

//ゲームスクリーンクラス
class CGameScreen : public CScreen
{
private:
	int m_Timer = 0;
	CImage* m_Image = 0;
public:
	CGameScreen();
	~CGameScreen();
	void Update();
	void Draw() const;
};
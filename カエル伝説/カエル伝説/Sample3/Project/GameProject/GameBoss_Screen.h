#pragma once

//ヘッダーファイル
#include"Global.h"
#include"screen.h"

//ゲームスクリーンクラス
class CGameBossScreen : public CScreen
{
private:
	int m_Timer = 0;
	CImage* m_Image = 0;
public:
	CGameBossScreen();
	~CGameBossScreen();
	void Update();
	void Draw() const;
};
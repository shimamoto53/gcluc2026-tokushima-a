#pragma once

//ヘッダーファイル
#include "Global.h"
#include "screen.h"

//タイトルスクリーンクラス
class CTitleScreen : public CScreen
{
private:
	int m_Timer = 0;
	CImage* m_Image = 0;
public:
	CTitleScreen();
	~CTitleScreen();
	void Update();
	void Draw();
};

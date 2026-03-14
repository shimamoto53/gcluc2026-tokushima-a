#pragma once

//ゲームスクリーンの種類
enum SCREEN {
	TITLE_SCREEN,
	GAME_SCREEN,
	GAMEBOSS_SCREEN,
	GAMECLEAR_SCREEN,
	GAMEOVER_SCREEN
};

class CScreen
{
protected:
	int m_State;
public:
	CScreen() {}
	virtual ~CScreen() {}

	virtual void Update() {}
	virtual void Draw() const {}
	//SCREEN GetNextScreen() const { return(m_State); } //次のスクリーンを示す

	int GetState()
	{
		return m_State;
	}
};
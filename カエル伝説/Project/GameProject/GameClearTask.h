#pragma once
#include "Task.h"

class GameClearTask : public Task
{
private:

    int m_select;
    int m_clearTime;  // ƒNƒŠƒAŠÔ

    CImage* mp_clear; // ‰æ‘œ
    CImage* mp_restart;
    CImage* mp_titleBtn;
    CImage* mp_exit;
    CImage* mp_marker;


public:
    GameClearTask();
    ~GameClearTask();

    void Update() override;
    void Render() override;
};
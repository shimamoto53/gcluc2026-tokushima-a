#pragma once
#include "Task.h"

class GameOverTask : public Task
{
private:
    int m_select;

    CImage* mp_over; // ‰æ‘œ
    CImage* mp_restart;
    CImage* mp_titleBtn;
    CImage* mp_exit;
    CImage* mp_marker;

public:
    GameOverTask();
    ~GameOverTask();

    void Update() override;
    void Render() override;
};
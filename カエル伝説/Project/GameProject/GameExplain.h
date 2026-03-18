#pragma once
#include "Task.h"

class GameExplainTask : public Task
{
private:
    int m_select;

    CImage* mp_explain; // ‰æ‘œ
    CImage* mp_start;
    CImage* mp_title;
    CImage* mp_marker;

public:
    GameExplainTask();
    ~GameExplainTask();

    void Update() override;
    void Render() override;
};
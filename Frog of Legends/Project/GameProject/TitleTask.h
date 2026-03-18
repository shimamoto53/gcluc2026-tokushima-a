#pragma once
#include "Task.h"

class TitleTask : public Task
{
private:

    int m_select;

    CImage* mp_title;
    CImage* mp_start;
    CImage* mp_exit;
    CImage* mp_explain;
    CImage* mp_marker;

public:

    TitleTask();
    ~TitleTask();

    void Update() override;
    void Render() override;
};
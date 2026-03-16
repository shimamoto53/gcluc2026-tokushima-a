#include "Timer.h"
#include "DebugPrint.h"

time_t Timer::startTime;

void Timer::Start()
{
    startTime = time(NULL);

    CREATE_FONT_F("timer", "C:\\Windows\\Fonts\\msgothic.ttc", 50);
}

void Timer::Update()
{
    int elapsed = (int)(time(NULL) - startTime);
    int remain = 60 - elapsed;

    if (remain < 0) remain = 0;

    int min = remain / 60;
    int sec = remain % 60;

    DebugPrint::Print("TIME %d:%02d", min, sec);
    FONT("timer")->Draw(1750, 70, 1, 1, 1, "%d:%02d", min, sec);

    if (remain <= 0)
    {
        DebugPrint::Print("TIME UP");
    }
}
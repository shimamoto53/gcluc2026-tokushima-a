#include "Timer.h"
#include "DebugPrint.h"

time_t Timer::startTime;

void Timer::Start()
{
    startTime = time(NULL);
}

void Timer::Update()
{
    int elapsed = (int)(time(NULL) - startTime);
    int remain = 60 - elapsed;
    int min = remain / 60;
    int sec = remain % 60;

    DebugPrint::Print("TIME %d:%02d", min, sec);

    if (remain <= 0)
    {
        DebugPrint::Print("TIME UP");
    }
}
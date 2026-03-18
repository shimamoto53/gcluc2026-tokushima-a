#include "Timer.h"
#include "DebugPrint.h"

time_t Timer::startTime;
int Timer::resultTime = 0;

void Timer::Start()
{
    startTime = time(NULL);
}

void Timer::Update()
{
    int elapsed = (int)(time(NULL) - startTime);
    int remain = 180 - elapsed;
    int min = remain / 60;
    int sec = remain % 60;

    DebugPrint::Print("TIME %d:%02d", min, sec);

    if (remain <= 0)
    {
        DebugPrint::Print("TIME UP");
    }
}

int Timer::GetElapsed()
{
    return (int)(time(NULL) - startTime);
}

int Timer::GetRemaining()  
{
    int limit = 60;
    int elapsed = GetElapsed();

    return limit - elapsed;
}

int Timer::GetResult()
{
    return resultTime;
}
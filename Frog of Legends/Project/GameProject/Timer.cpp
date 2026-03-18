#include "Timer.h"
#include "DebugPrint.h"

time_t Timer::startTime;
int Timer::resultTime = 0;
static int remain = 60;

void Timer::Start()
{
    startTime = time(NULL);

    CREATE_FONT_F("timer", "C:\\Windows\\Fonts\\meiryo.ttc", 100);
}

void Timer::Update()
{
    int elapsed = (int)(time(NULL) - startTime);
    int remain = 180 - elapsed;

    if (remain < 0)
        remain = 0;

    int min = remain / 60;
    int sec = remain % 60;

  //  DebugPrint::Print("TIME %d:%02d", min, sec);

    if (remain <= 0)
    {
        DebugPrint::Print("TIME UP");
    }
    FONT("timer")->Draw(1650, 130, 1, 1, 1, "%d:%02d", min, sec);
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
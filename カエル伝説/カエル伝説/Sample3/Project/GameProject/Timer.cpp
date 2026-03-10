#include "Timer.h"

int Timer::timer = 0;

void Timer::Update()
{
    timer++;
}

void Timer::Reset()
{
    timer = 0;
}

float Timer::GetTime()
{
    return timer / 60.0f;
}

int Timer::GetMinute()
{
    return (timer / 60) / 60;
}

int Timer::GetSecond()
{
    return (timer / 60) % 60;
}
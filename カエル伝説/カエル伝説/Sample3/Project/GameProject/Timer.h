#pragma once
#include <time.h>

class Timer
{
private:
    static time_t startTime;

public:
    static void Start();
    static void Update();
};
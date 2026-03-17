#pragma once
#include <time.h>

class Timer
{
private:
    static time_t startTime;
    static int resultTime;

public:
    static void Start();
    static void Update();
    static int GetResult();
};
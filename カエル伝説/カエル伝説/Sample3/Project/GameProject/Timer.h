#pragma once


class Timer
{
private:
    static int timer;

public:
    static void Update();   // 毎フレーム呼ぶ
    static void Reset();    // タイマーリセット
    static float GetTime(); // 秒取得
    static int GetMinute(); // 分取得
    static int GetSecond(); // 秒取得
    static void Draw();
};
#pragma once
#include "task.h"

class Score : public Task
{
public:
	static void Add(int value);
	static int Get();

private:
	static int score;
};
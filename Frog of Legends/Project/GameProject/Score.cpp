#include "Score.h"

int Score::score = 0;

void Score::Add(int value)
{
	score += value;
}

int Score::Get()
{
	return score;
}

void Score::Reset()
{
	score = 0;
}
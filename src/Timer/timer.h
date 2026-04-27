#pragma once
#include "SDL3/SDL.h"

class timer
{
public:
	timer(float second);
	float getTime();
	bool checkTime();
	float getLinearProgress();
	float getEasedProgress();

private:
	Uint64 FirstTime;
	float Max;
};
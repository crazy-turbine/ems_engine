#include "src/Timer/timer.h"
#include <cmath>

timer::timer(float second)
	:Max(second)
{
	FirstTime = SDL_GetTicks();
}

float timer::getTime()
{
    Uint64 CurrentTime= SDL_GetTicks();
    return (CurrentTime - FirstTime)/1000.0f;
}

bool timer::checkTime()
{
    Uint64 CurrentTime = SDL_GetTicks();
	return (CurrentTime - FirstTime) / 1000.0f > Max;
}

float timer::getLinearProgress()
{
    Uint64 CurrentTime = SDL_GetTicks();
	if (Max == NULL)
		return NULL;
	if ((CurrentTime - FirstTime) / 1000.0f > Max)
        return 1.0f;
	return (CurrentTime - FirstTime) / 1000.0f / Max;
}

float timer::getEasedProgress()
{
    Uint64 CurrentTime = SDL_GetTicks();
	if (Max == NULL)
		return NULL;
	if ((CurrentTime - FirstTime) / 1000.0f > Max)
        return 1.0f;
	float t = (CurrentTime - FirstTime) / 1000.0f / Max;
    //t = 3 * pow(t, 2) - 2 * pow(t, 3);
	t = 1 - pow(2, -10 * t);
	//t = 1 - pow(1-t, 5);
    return t;
}
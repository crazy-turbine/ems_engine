#include "src/Timer/timerManager.h"

std::unordered_map < std::string, std::unique_ptr<timer>> TimerMap;

bool createTimer(std::string timerID, float max_second)
{
	if (TimerMap.contains(timerID))
	{
		return false;
	}
	TimerMap.emplace(timerID, std::make_unique<timer>(max_second));
	return true;
}
void deleteTimer(std::string timerID)
{
	if (TimerMap.contains(timerID))
		TimerMap.erase(timerID);
}
void clearAllTimer()
{
	TimerMap.clear();
}
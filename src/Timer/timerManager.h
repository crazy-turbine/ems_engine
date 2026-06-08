#pragma once
#include <unordered_map>
#include "src/Common/enum.h"
#include "timer.h"
#include <memory>
#include <string>

extern std::unordered_map < std::string, std::unique_ptr<timer>> TimerMap;

bool createTimer(std::string timerID, float max_second);
void deleteTimer(std::string timerID);
void clearAllTimer();
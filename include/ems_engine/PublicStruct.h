#pragma once
#include <string>

namespace ems_engine
{
	struct EngineState
	{
		float mouseX = 0;
		float mouseY = 0;
		bool isDragging = false;
		//Entity* TargetButton = nullptr;
		bool isRefreshText = false;
		bool Vsync = true;
		bool fullscreen = true;
		bool mouseGrab = true;
		std::string Language = "no";
		float volume = 0.0f;
	};
	struct Position
	{
		float x = 0.0f, y = 0.0f;
	};
	struct Size
	{
		float w = 0.0f, h = 0.0f;
	};
	struct Rect
	{
		float x = 0.0f, y = 0.0f, w = 0.0f, h = 0.0f;
	};
	struct Color
	{
		uint8_t r = 255, g = 255, b = 255, a = 255;
	};
}

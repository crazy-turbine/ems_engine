#pragma once
#include <string>
#include <SDL3/SDL.h>
#include<memory>
#include "src/Common/idConverter.h"

class audio;
class Render;

namespace ems
{
	class Engine
	{
	public:
		Engine();
		bool init();
	private:
		bool initSDL();
		void showError(std::string msg, std::string err);
		bool checkResolution();
		bool set_cursor();
		void handleEvents();
		SDL_DisplayID Display;
		const SDL_DisplayMode* displayMode;
		std::unique_ptr<Render> render_sys;
		std::unique_ptr<audio> sound_sys;
		int windowWidth;
		int windowHeight;
	};
}
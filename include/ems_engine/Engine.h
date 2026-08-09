#pragma once
#include <string>
#include <SDL3/SDL.h>
#include<memory>
#include "src/Common/idConverter.h"

class audio;
class Render;
class InputManager;
class ActionBehavior;
class ActionPolicyManager;

namespace ems
{
	class Engine
	{
	public:
		Engine();
		~Engine();
		bool init();
		void run();
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
		std::unique_ptr<InputManager> input_mgr;
		std::unique_ptr<ActionBehavior> button_def;
		std::unique_ptr<ActionPolicyManager> ap_mgr;
		int windowWidth;
		int windowHeight;
	};
}
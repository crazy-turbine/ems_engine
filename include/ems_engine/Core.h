#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <memory>
#include <functional>
#include <vector>
#include "src/Common/idConverter.h"



namespace ems_engine
{
	class audio;
	class Render;
	class RenderManager;
	class InputManager;
	class ActionBehavior;
	class ActionPolicyManager;
	class SceneManager;

	class Core
	{
	public:
		Core();
		~Core();
		bool init(std::function<void(Core*)> custom_init = {});
		void run(std::function<void(Core*)> custom_update = {});

		void setActionGroup(std::string group_name, std::function<void()> group_function);
		ActionPolicyManager* getActionPolicyManager();

	private:
		bool initSDL();
		void showError(std::string msg, std::string err);
		bool checkResolution();
		bool set_cursor();
		void handleEvents();
		SDL_DisplayID Display;
		SDL_Event event{};
		const SDL_DisplayMode* displayMode;
		std::unique_ptr<Render> render_sys;
		std::unique_ptr<RenderManager> render_mgr;
		std::unique_ptr<audio> sound_sys;
		std::unique_ptr<InputManager> input_mgr;
		std::unique_ptr<ActionBehavior> button_def;
		std::unique_ptr<ActionPolicyManager> ap_mgr;
		std::unique_ptr<SceneManager> ui_mgr;
		bool app = false;
		int windowWidth;
		int windowHeight;
	};
}
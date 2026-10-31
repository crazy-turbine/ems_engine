#pragma once
#include <string>
#include <memory>
#include <functional>
#include <vector>
#include "PublicStruct.h"


namespace ems_engine
{
	class audio;
	class Render;
	class RenderManager;
	class InputManager;
	class ActionBehavior;
	class ActionPolicyManager;
	class SceneManager;
	class ID_Converter;
	class ResourceManager;
	class SceneAPI;
	class ActionAPI;

	class Core
	{
	public:
		Core();
		~Core();
		bool init(std::function<void(Core*)> custom_init = {});
		void run(std::function<bool(Core*)> custom_update = {});

		void setActionGroup(std::string group_name, std::function<void()> group_function);
		ActionPolicyManager* getActionPolicyManager();
		

		const EngineState& getEngineConfig();

		SceneAPI* UI_SceneAPI();


	private:
		bool initSDL();
		void showError(std::string msg, std::string err);
		bool checkResolution();
		bool set_cursor();
		void handleEvents();

		void set_config();

		struct SDLData;
		std::unique_ptr<SDLData> sdl_data; 
		std::unique_ptr<EngineState> state;
		std::unique_ptr<Render> render_sys;
		std::unique_ptr<RenderManager> render_mgr;
		std::unique_ptr<audio> sound_sys;
		std::unique_ptr<InputManager> input_mgr;
		std::unique_ptr<ActionBehavior> button_def;
		std::unique_ptr<ActionPolicyManager> ap_mgr;
		std::unique_ptr<SceneManager> ui_mgr;
		std::unique_ptr<ResourceManager> rc_mgr;
		//std::unique_ptr<ID_Converter> id_converter;

		//API
		std::unique_ptr<SceneAPI> ui_scene_api_;
		std::unique_ptr<ActionAPI> action_api_;

		bool app = false;
		int windowWidth;
		int windowHeight;
		EngineState EngineConfig;
	};
}
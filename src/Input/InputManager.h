#pragma once
#include <memory>
#include <string>

namespace ems_engine
{
	enum class mouse_code;
	class ActionBehavior;
	class SceneManager;
	class Render;
	class KeyboardInput;
	class MouseInput;
	//class GamepadInput;
	//class TouchInput;

	class InputManager
	{
	public:
		InputManager(ActionBehavior* bh, SceneManager* sc_mgr, Render* render);
		~InputManager();
		void InputRefresh();
	private:
		ActionBehavior* a_bh = nullptr;
		SceneManager* scene_mgr = nullptr;
		Render* render_sys = nullptr;
		std::unique_ptr<KeyboardInput> Kinput;
		std::unique_ptr<MouseInput> Minput;

		std::string click_down_objID = "";
		std::string click_up_objID = "";
		//std::unique_ptr<GamepadInput> Ginput;
		//std::unique_ptr<TouchInput> Tinput;
	};
}

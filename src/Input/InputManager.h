#pragma once
#include <memory>

class ActionBehavior;
class KeyboardInput;
//class MouseInput;
//class GamepadInput;
//class TouchInput;

class InputManager
{
public:
	InputManager(ActionBehavior* bh);
	~InputManager();
	void InputRefresh();
private:
	ActionBehavior* b_bh;
	std::unique_ptr<KeyboardInput> Kinput;
	//std::unique_ptr<MouseInput> Minput;
	//std::unique_ptr<GamepadInput> Ginput;
	//std::unique_ptr<TouchInput> Tinput;
};
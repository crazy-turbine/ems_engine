#pragma once
#include <memory>

class button_behavior;
class KeyboardInput;
//class MouseInput;
//class GamepadInput;
//class TouchInput;

class InputManager
{
public:
	InputManager(button_behavior* bh);
	~InputManager();
	void InputRefresh();
private:
	button_behavior* b_bh;
	std::unique_ptr<KeyboardInput> Kinput;
	//std::unique_ptr<MouseInput> Minput;
	//std::unique_ptr<GamepadInput> Ginput;
	//std::unique_ptr<TouchInput> Tinput;
};
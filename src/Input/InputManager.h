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
	void InputRefresh();
private:
	button_behavior* b_bh;
	KeyboardInput Kinput;
	//MouseInput Minput;
	//GamepadInput Ginput;
	//TouchInput Tinput;
};
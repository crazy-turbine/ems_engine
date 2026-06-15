#include "InputManager.h"
#include "KeyboardInput.h"
#include "src/Common/enum.h"
#include "src/Action/button_behavior.h"
#include <vector>

InputManager::InputManager(button_behavior* bh)
{
	b_bh = bh;
	Kinput = std::make_unique<KeyboardInput>();
	//Minput = std::make_unique<MouseInput>();
	//Ginput = std::make_unique<GamepadInput>();
	//Tinput = std::make_unique<TouchInput>();
}
InputManager::~InputManager() = default;
void InputManager::InputRefresh()
{
	std::vector<std::pair<keyboard_code, key_state>> Klist;
	std::vector<std::pair<mouse_code, key_state>> Mlist;
	if (Kinput->UpdateState(Klist))
	{
		for (const auto Key : Klist)
		{
			b_bh->ButtonExcute(Key);
		}
	}
}
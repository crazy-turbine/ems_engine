#include "InputManager.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "src/Common/enum.h"
#include "src/Action/ActionBehavior.h"
#include <vector>

namespace ems_engine
{

	InputManager::InputManager(ActionBehavior* bh)
	{
		a_bh = bh;
		Kinput = std::make_unique<KeyboardInput>();
		Minput = std::make_unique<MouseInput>();
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
				a_bh->ButtonExcute(Key.first);
			}
		}
		float MouseX, MouseY;
		if (Minput->UpdateState(Mlist,MouseX,MouseY))
		{
			for (const auto Key : Mlist)
			{
				a_bh->ButtonExcute(Key.first);
				if (Key.first == mouse_code::Left)
				{

				}
			}

		}
	}
}

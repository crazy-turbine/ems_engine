#include "InputManager.h"
#include "KeyboardInput.h"
#include "src/Common/enum.h"
#include "src/Action/button_behavior.h"
#include <vector>

InputManager::InputManager(button_behavior* bh)
{
	b_bh = bh;
}

void InputManager::InputRefresh()
{
	std::vector<keyboard_code> Klist;
	if (Kinput.getState(Klist))
	{
		for (const auto Key : Klist)
		{
			b_bh->ButtonExcute(Key);
		}
	}
}
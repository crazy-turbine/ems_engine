#include "MouseInput.h"

#include <SDL3/SDL.h>
#include "src/Common/enum.h"


bool MouseInput::UpdateState(std::vector<std::pair<mouse_code, key_state>>& key_list, float& x, float& y)
{
	key_list.clear();
	CurrState = SDL_GetMouseState(&x, &y);
	for (int i = 1; i <= 5; i++)
	{
		bool isCurrDown = (CurrState & SDL_BUTTON_MASK(i)) != 0;
		bool isPrevDown = (PrevState & SDL_BUTTON_MASK(i)) != 0;
		if (!isCurrDown && (isCurrDown == isPrevDown))
		{
			continue;
		}
		else if (mouse_code keycode = KeycodeConvert(i); keycode != mouse_code::Unknown)
		{
			key_state PressState;
			if (isCurrDown == isPrevDown)
			{
				PressState = key_state::hold;
			}
			if (isCurrDown && !isPrevDown)
			{
				PressState = key_state::down;
			}
			if (!isCurrDown && isPrevDown)
			{
				PressState = key_state::up;
			}
			key_list.push_back({ keycode, PressState });
		}
	}
	PrevState = CurrState;
	return !key_list.empty();
}

#define cv(x,y) case x: return mouse_code::y; break
mouse_code MouseInput::KeycodeConvert(Uint8 keynum)
{
	switch (keynum)
	{
		cv(SDL_BUTTON_LEFT, Left);
		cv(SDL_BUTTON_RIGHT, Right);
		cv(SDL_BUTTON_MIDDLE, Middle);
		cv(SDL_BUTTON_X1, X1);
		cv(SDL_BUTTON_X2, X2);
	default: return mouse_code::Unknown;
	}
}
#undef cv
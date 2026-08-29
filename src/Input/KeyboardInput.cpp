#include "KeyboardInput.h"
#include <SDL3/SDL.h>
#include "src/Common/enum.h"


namespace ems_engine
{

	bool KeyboardInput::UpdateState(std::vector<std::pair<keyboard_code, key_state>>& key_list)
	{
		key_list.clear();
		int numkeys;
		CurrState = SDL_GetKeyboardState(&numkeys);

		if (PrevState.size() != static_cast<std::size_t>(numkeys))
		{
			PrevState.assign(numkeys, false);
		}

		for (int i = 0; i < numkeys; i++)
		{
			bool isCurrDown = CurrState[i];
			bool isPrevDown = PrevState[i];
			if (!isCurrDown && (isCurrDown == isPrevDown))
			{
				continue;
			}
			else if (keyboard_code keycode = KeycodeConvert(i); keycode != keyboard_code::Unknown)
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
		std::copy(CurrState, CurrState + numkeys, PrevState.begin());
		return !key_list.empty();
	}

#define cv(x,y) case x: return keyboard_code::y; break
	keyboard_code KeyboardInput::KeycodeConvert(int keynum)
	{
		switch (keynum)
		{
			cv(SDL_SCANCODE_0, Num0);
			cv(SDL_SCANCODE_1, Num1);
			cv(SDL_SCANCODE_2, Num2);
			cv(SDL_SCANCODE_3, Num3);
			cv(SDL_SCANCODE_4, Num4);
			cv(SDL_SCANCODE_5, Num5);
			cv(SDL_SCANCODE_6, Num6);
			cv(SDL_SCANCODE_7, Num7);
			cv(SDL_SCANCODE_8, Num8);
			cv(SDL_SCANCODE_9, Num9);

			cv(SDL_SCANCODE_KP_0, Numpad0);
			cv(SDL_SCANCODE_KP_1, Numpad1);
			cv(SDL_SCANCODE_KP_2, Numpad2);
			cv(SDL_SCANCODE_KP_3, Numpad3);
			cv(SDL_SCANCODE_KP_4, Numpad4);
			cv(SDL_SCANCODE_KP_5, Numpad5);
			cv(SDL_SCANCODE_KP_6, Numpad6);
			cv(SDL_SCANCODE_KP_7, Numpad7);
			cv(SDL_SCANCODE_KP_8, Numpad8);
			cv(SDL_SCANCODE_KP_9, Numpad9);

			cv(SDL_SCANCODE_F1, F1);
			cv(SDL_SCANCODE_F2, F2);
			cv(SDL_SCANCODE_F3, F3);
			cv(SDL_SCANCODE_F4, F4);
			cv(SDL_SCANCODE_F5, F5);
			cv(SDL_SCANCODE_F6, F6);
			cv(SDL_SCANCODE_F7, F7);
			cv(SDL_SCANCODE_F8, F8);
			cv(SDL_SCANCODE_F9, F9);
			cv(SDL_SCANCODE_F10, F10);
			cv(SDL_SCANCODE_F11, F11);
			cv(SDL_SCANCODE_F12, F12);
			cv(SDL_SCANCODE_F13, F13);
			cv(SDL_SCANCODE_F14, F14);
			cv(SDL_SCANCODE_F15, F15);
			cv(SDL_SCANCODE_F16, F16);
			cv(SDL_SCANCODE_F17, F17);
			cv(SDL_SCANCODE_F18, F18);
			cv(SDL_SCANCODE_F19, F19);
			cv(SDL_SCANCODE_F20, F20);
			cv(SDL_SCANCODE_F21, F21);
			cv(SDL_SCANCODE_F22, F22);
			cv(SDL_SCANCODE_F23, F23);
			cv(SDL_SCANCODE_F24, F24);

			cv(SDL_SCANCODE_A, A);
			cv(SDL_SCANCODE_B, B);
			cv(SDL_SCANCODE_C, C);
			cv(SDL_SCANCODE_D, D);
			cv(SDL_SCANCODE_E, E);
			cv(SDL_SCANCODE_F, F);
			cv(SDL_SCANCODE_G, G);
			cv(SDL_SCANCODE_H, H);
			cv(SDL_SCANCODE_I, I);
			cv(SDL_SCANCODE_J, J);
			cv(SDL_SCANCODE_K, K);
			cv(SDL_SCANCODE_L, L);
			cv(SDL_SCANCODE_M, M);
			cv(SDL_SCANCODE_N, N);
			cv(SDL_SCANCODE_O, O);
			cv(SDL_SCANCODE_P, P);
			cv(SDL_SCANCODE_Q, Q);
			cv(SDL_SCANCODE_R, R);
			cv(SDL_SCANCODE_S, S);
			cv(SDL_SCANCODE_T, T);
			cv(SDL_SCANCODE_U, U);
			cv(SDL_SCANCODE_V, V);
			cv(SDL_SCANCODE_W, W);
			cv(SDL_SCANCODE_X, X);
			cv(SDL_SCANCODE_Y, Y);
			cv(SDL_SCANCODE_Z, Z);

			cv(SDL_SCANCODE_UP, Up);
			cv(SDL_SCANCODE_DOWN, Down);
			cv(SDL_SCANCODE_LEFT, Left);
			cv(SDL_SCANCODE_RIGHT, Right);

			cv(SDL_SCANCODE_LCTRL, LCtrl);
			cv(SDL_SCANCODE_LSHIFT, LShift);
			cv(SDL_SCANCODE_LALT, LAlt);
			cv(SDL_SCANCODE_LGUI, LSystem);
			cv(SDL_SCANCODE_RCTRL, RCtrl);
			cv(SDL_SCANCODE_RSHIFT, RShift);
			cv(SDL_SCANCODE_RALT, RAlt);
			cv(SDL_SCANCODE_RGUI, RSystem);

			cv(SDL_SCANCODE_BACKSPACE, Backspace);
			cv(SDL_SCANCODE_RETURN, Enter);
			cv(SDL_SCANCODE_TAB, Tab);
			cv(SDL_SCANCODE_ESCAPE, Esc);
			cv(SDL_SCANCODE_MENU, Menu);
			cv(SDL_SCANCODE_SPACE, Space);

			cv(SDL_SCANCODE_CAPSLOCK, CapsLock);
			cv(SDL_SCANCODE_NUMLOCKCLEAR, NumLock);
			cv(SDL_SCANCODE_SCROLLLOCK, ScrollLock);
			cv(SDL_SCANCODE_PAUSE, Pause);
			cv(SDL_SCANCODE_PRINTSCREEN, PrintScreen);

			cv(SDL_SCANCODE_INSERT, Insert);
			cv(SDL_SCANCODE_DELETE, Delete);
			cv(SDL_SCANCODE_HOME, Home);
			cv(SDL_SCANCODE_END, End);
			cv(SDL_SCANCODE_PAGEUP, PageUp);
			cv(SDL_SCANCODE_PAGEDOWN, PageDown);

			cv(SDL_SCANCODE_MINUS, Minus);
			cv(SDL_SCANCODE_EQUALS, Equals);
			cv(SDL_SCANCODE_LEFTBRACKET, LBracket);
			cv(SDL_SCANCODE_RIGHTBRACKET, RBracket);
			cv(SDL_SCANCODE_BACKSLASH, Backslash);
			cv(SDL_SCANCODE_SEMICOLON, Semicolon);
			cv(SDL_SCANCODE_APOSTROPHE, Apostrophe);
			cv(SDL_SCANCODE_COMMA, Comma);
			cv(SDL_SCANCODE_PERIOD, Period);
			cv(SDL_SCANCODE_SLASH, Slash);
			cv(SDL_SCANCODE_GRAVE, Grave);

		default: return keyboard_code::Unknown;
		}
	}
#undef cv
}

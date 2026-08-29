#pragma once

namespace ems_engine
{

	enum class FlipType
	{
		None,
		Horizontal,
		Vertical
	};
	enum class layer_ID
	{
		back = 0,
		on_back = 100,
		map = 200,
		on_map = 300,
		mapEntity = 400,
		on_mapEntity = 500,
		UIobject = 600,
		on_UIobject = 700,
		UIbutton = 800,
		on_UIbutton = 900,
		top = 1000

	};
	enum class line_type
	{
		single,
		multi
	};
	enum class text_type
	{
		default_static,
		default_dynamic,
		dialog,
		control_tips
	};
	enum class scene_ani_state
	{
		aniIN,
		aniOUT,
		None
	};
	enum class key_state
	{
		down,
		hold,
		up
	};
	enum class keyboard_code
	{
		Unknown = 0,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,
		Numpad1, Numpad2, Numpad3, Numpad4, Numpad5,
		Numpad6, Numpad7, Numpad8, Numpad9, Numpad0,
		F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
		F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
		Up, Down, Left, Right,
		LCtrl, LShift, LAlt, LSystem, RCtrl, RShift, RAlt, RSystem,
		Backspace, Enter, Tab, Esc, Menu, Space,
		CapsLock, NumLock, ScrollLock, Pause, PrintScreen,
		Insert, Delete, Home, End, PageUp, PageDown,
		Minus,      // -
		Equals,     // =
		LBracket,	// [
		RBracket,	// ]
		Backslash,  // "\"
		Semicolon,  // ;
		Apostrophe, // '
		Comma,      // ,
		Period,     // .
		Slash,      // /
		Grave,      // ~
	};

	enum class mouse_code
	{
		Unknown = 0,
		Left,
		Middle,
		Right,
		X1,
		X2
	};
	enum class gamepad_code
	{
		Unknown = 0,
		North, East, South, West,
		Start,		// XB:Menu PS:Options NS:+
		Back,		// XB:View PS:Share NS:-
		Guide,		// Logo Button
		Up, Down, Left, Right,

		LShoulder, RShoulder,
		LTrigger, RTrigger,

		LStickButton,
		LStickUp, LStickUpRight, LStickRight, LStickDownRight,
		LStickDown, LStickDownLeft, LStickLeft, LStickUpLeft,

		RStickButton,
		RStickUp, RStickUpRight, RStickRight, RStickDownRight,
		RStickDown, RStickDownLeft, RStickLeft, RStickUpLeft,

		LPaddle1, RPaddle1,
		LPaddle2, RPaddle2,

		Misc1, Misc2, Misc3, Misc4, Misc5, Misc6,

		TouchPad

	};
}

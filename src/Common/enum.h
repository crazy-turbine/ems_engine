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

}

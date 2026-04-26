#pragma once

enum class FlipType
{
	None,
	Horizontal,
	Vertical
};
enum class layer_ID
{
	back = 0,
	on_back,
	map,
	on_map,
	mapEntity,
	on_mapEntity,
	UIobject,
	on_UIobject,
	UIbutton,
	on_UIbutton,
	top
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
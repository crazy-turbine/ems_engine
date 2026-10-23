#pragma once
#include <SDL3/SDL.h>
#include "enum.h"
#include <string>
#include <vector>


namespace ems_engine
{

	//class Entity;

	struct RenderConfig
	{
		uint64_t textureID = 0;

		float x = 0.0f;
		float y = 0.0f;
		float w = 0.0f;
		float h = 0.0f;

		uint8_t alpha = 255;

		double angle = 0.0f;
		bool useDefaultCenter = true;
		float PointX = 0.0f;
		float PointY = 0.0f;

		FlipType flip = FlipType::None;
	};

	


	struct EntityConfig
	{
		std::string sceneID;
		int layer;
		std::string actionID;
		std::string slide_button;
		float x, y, w, h;
		int series_num = 0;
		std::vector<std::string> TexturePath;
	};

	struct JsonTarget
	{
		std::string jsonPath;
		std::string jsptr;
	};

	struct TextConfig
	{
		line_type Ltype;
		text_type Ttype;
		float size, startX, endX, y;
		SDL_Color color;
		std::string path;
		std::vector<JsonTarget> conditionTarget;
		std::vector<JsonTarget> default_text;
		std::vector<JsonTarget> haveValue_text;
	};


	

	struct KeyboardConditionalKey
	{
		keyboard_code code;
		key_state state;
		std::string condition;

		bool operator ==(const KeyboardConditionalKey& other) const
		{
			return
				code == other.code &&
				state == other.state &&
				condition == other.condition;
		}
	};
}

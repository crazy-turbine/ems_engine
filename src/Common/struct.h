#pragma once
#include <SDL3/SDL.h>
#include "enum.h"
#include <string>
#include <vector>

struct RenderConfig
{
	SDL_Texture* Texture;

	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;

	double angle = 0;
	bool useDefaultCenter = true;
	float PointX = 0;
	float PointY = 0;

	FlipType flip = FlipType::None;
};

struct Vector2f
{
	Vector2f()
		:x(0.0f), y(0.0f)
	{
	}
	Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y)
	{
	}
	void print()
	{
		//std::cout << x << "," << y << std::endl;
	}
	float x, y;
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

#pragma once
#include "enum.h"

struct RenderConfig
{
	std::string texture_path;
	std::string sceneID;

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

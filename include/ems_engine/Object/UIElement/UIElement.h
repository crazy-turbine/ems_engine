#pragma once
#include "include/ems_engine/Object/TextureObject.h"



namespace ems_engine
{
	class UIElement :public TextureObject
	{
	public:
		UIElement() = default;
		UIElement(float x, float y, float w, float h, uint64_t textureID);
	};
}
#include "UIElement.h"


namespace ems_engine
{
	UIElement::UIElement(float x, float y, float w, float h, uint64_t textureID)
		:TextureObject(x,y,w,h,textureID)
	{
	}
}
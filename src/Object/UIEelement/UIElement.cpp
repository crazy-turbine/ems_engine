#include "UIElement.h"

namespace ems_engine
{
	UIElement::UIElement(float x, float y, float w, float h, uint64_t textureID)
		:Object(x,y,w,h), textureID_(textureID)
	{
	}
	void UIElement::setAssetID(uint64_t textureID)
	{
		textureID_ = textureID;
	}
	uint64_t UIElement::getAssetID() const
	{
		return textureID_;
	}
}
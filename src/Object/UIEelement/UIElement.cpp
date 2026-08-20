#include "UIElement.h"

namespace ems_engine
{
	UIElement::UIElement(float x, float y, float w, float h, uint64_t textureID)
		:Object(x,y,w,h), current_textureID_(textureID)
	{
	}
	void UIElement::setCurrentTextureID(uint64_t textureID)
	{
		current_textureID_ = textureID;
	}
	uint64_t UIElement::getCurrentTextureID() const
	{
		return current_textureID_;
	}
	void UIElement::setVisible(bool visible)
	{
		visible_ = visible;
	}
	bool UIElement::isVisible() const
	{
		return visible_;
	}
}
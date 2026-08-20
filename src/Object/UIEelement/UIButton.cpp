#include "UIButton.h"
#include <iostream>
#include "Common/toHash.h"

namespace ems_engine
{
	bool UIButton::contains(float mouseX, float mouseY)
	{
        if (isVisible() &&
            mouseX >= getPos().x &&
            mouseX <= getPos().x + getSize().w &&
            mouseY >= getPos().y &&
            mouseY <= getPos().y + getSize().h)
        {   
            return true;
        }
        else
        {
            return false;
        }
	}

    void UIButton::setDefaultState(uint64_t state)
    {
        if (FindTextureState(state))
            default_state = state;
        else
            std::cout << "[Error]:TextureState Not Found!" << std::endl;
    }
    void UIButton::setHoverState(uint64_t state)
    {
        if (FindTextureState(state))
            hover_state = state;
        else
            std::cout << "[Error]:TextureState Not Found!" << std::endl;
    }
    void UIButton::setDefaultState(std::string state)
    {
        setDefaultState(string_toHash(state));
    }
    void UIButton::setHoverState(std::string state)
    {
        setHoverState(string_toHash(state));
    }
    void UIButton::setHoverOn(bool hover_on)
    {
        if (hover_on)
        {
            setCurrentVisualState(hover_state);
        }
        else
        {
            setCurrentVisualState(default_state);
        }
    }
}
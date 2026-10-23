#include "include/ems_engine/Object/UIElement/UIButton.h"
#include <iostream>
#include "Common/toHash.h"

namespace ems_engine
{
    UIButton::UIButton()
    {
        setDefaultState("Default");
        setHoverState("Hover");
    }
    UIButton::UIButton(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps, uint64_t df_state, uint64_t hov_state)
        :UIStateElement(x,y,w,h,visual_group,state,fps)
    {
        setDefaultState(df_state);
        setHoverState(hov_state);
    }
    UIButton::UIButton(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps, std::string df_state, std::string hov_state)
        :UIStateElement(x,y,w,h,visual_group,state,fps)
    {
        setDefaultState(df_state);
        setHoverState(hov_state);
    }
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
#include "UICheckBox.h"
#include "Common/toHash.h"
#include <iostream>

namespace ems_engine
{
    UICheckBox::UICheckBox()
    {
        std::vector<uint64_t> tmp_visual_group;
        tmp_visual_group.push_back(0);
        setVisualGroup(tmp_visual_group, "Checked"_xxHash);
        setVisualGroup(tmp_visual_group, "Hover"_xxHash);
        setCheckedState("Checked");
        setCheckedHoverState("Hover");
    }
    UICheckBox::UICheckBox(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps, uint64_t df_state, uint64_t hov_state, uint64_t chk_state, uint64_t chk_hov_state)
        :UIButton(x, y, w, h, visual_group, state, fps, df_state, hov_state)
    {
        std::vector<uint64_t> tmp_visual_group;
        tmp_visual_group.push_back(0);
        setVisualGroup(tmp_visual_group, chk_state);
        setVisualGroup(tmp_visual_group, chk_hov_state);
        setCheckedState(chk_state);
        setCheckedHoverState(chk_hov_state);
    }
    UICheckBox::UICheckBox(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps, std::string df_state, std::string hov_state, std::string chk_state, std::string chk_hov_state = "")
        :UIButton(x, y, w, h, visual_group, state, fps, df_state, hov_state)
    {
        if (chk_hov_state.empty())
            chk_hov_state = hov_state;
        std::vector<uint64_t> tmp_visual_group;
        tmp_visual_group.push_back(0);
        setVisualGroup(tmp_visual_group, string_toHash(chk_state));
        setVisualGroup(tmp_visual_group, string_toHash(chk_hov_state));
        setCheckedState(chk_state);
        setCheckedHoverState(chk_hov_state);
    }


    void UICheckBox::setCheckedState(uint64_t state)
    {
        if (FindTextureState(state))
            checked_state = state;
        else
            std::cout << "[Error]:TextureState Not Found!" << std::endl;
    }
    void UICheckBox::setCheckedHoverState(uint64_t state)
    {
        if (FindTextureState(state))
            checked_hover_state = state;
        else
            std::cout << "[Error]:TextureState Not Found!" << std::endl;
    }
    void UICheckBox::setCheckedState(std::string state)
    {
        setCheckedState(string_toHash(state));
    }
    void UICheckBox::setCheckedHoverState(std::string state)
    {
        setCheckedHoverState(string_toHash(state));
    }
    void UICheckBox::setCheckOn(bool check_on)
    {
        check = check_on;
        if (check_on)
        {
            setCurrentVisualState(checked_state);
        }
        else
        {
            setCurrentVisualState(default_state);
        }
    }
    bool UICheckBox::isCheckOn() const
    {
        return check;
    }
}
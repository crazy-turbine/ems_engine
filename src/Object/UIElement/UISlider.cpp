#include "include/ems_engine/Object/UIElement/UISlider.h"
#include <iostream>

namespace ems_engine
{
	UISlider::UISlider(float x, float y, float w, float h, const std::vector<std::string>& visual_group, uint64_t slidebar_textureID, std::string_view state, float fps, uint64_t df_state, uint64_t hov_state, bool horizon, float percentage)
		:UIButton(x, y, w, h, visual_group, state, fps, df_state, hov_state), horizon_(horizon), percentage_(percentage)
	{
		current_slidebar_textureID_ = slidebar_textureID;
		UpdatePercentage();
	}
	UISlider::UISlider(float x, float y, float w, float h, const std::vector<std::string>& visual_group, uint64_t slidebar_textureID, std::string_view state, float fps, std::string df_state, std::string hov_state, bool horizon, float percentage)
		:UIButton(x,y,w,h,visual_group,state,fps,df_state,hov_state), horizon_(horizon), percentage_(percentage)
	{
		current_slidebar_textureID_ = slidebar_textureID;
		UpdatePercentage();
	}

	void UISlider::setPercentage(float percentage)
	{
		if (percentage < 0.0f)
		{
			std::cout << "[Error]: Precentage out of range!(0.0~100.0)" << std::endl;
			percentage_ = 0;
		}
		else if (percentage > 100.0f)
		{
			std::cout << "[Error]: Precentage out of range!(0.0~100.0)" << std::endl;
			percentage_ = 100.0f;
		}
		percentage_ = percentage;
		UpdateSlideButtonPos();
	}
	float UISlider::getPercentage()
	{
		return percentage_;
	}

	void UISlider::setSlideButtonPos(float x, float y)
	{
		slidebutton_pos = { x,y };
	}
	Position UISlider::getSlideButtonPos()
	{
		return slidebutton_pos;
	}

	void UISlider::setHorizon(bool horizon)
	{
		horizon_ = horizon;
	}
	bool UISlider::isHorizon()
	{
		return horizon_;
	}

	void UISlider::setCurrentTextureID(uint64_t textureID, size_t index)
	{
		if (index == 0)
			current_textureID_ = textureID;
		else if (index == 1)
			current_slidebar_textureID_ = textureID;
	}
	uint64_t UISlider::getCurrentTextureID(size_t index) const
	{
		if (index == 0)
			return current_textureID_;
		else if (index == 1)
			return current_slidebar_textureID_;
	}

	void UISlider::UpdateSlideButtonPos()
	{
		if (horizon_)
		{
			float x = getPos().x + getSize().w * percentage_ / 100.0f;
			slidebutton_pos.x = x;
		}
		else
		{
			float y = getPos().y + getSize().h * percentage_ / 100.0f;
			slidebutton_pos.y = y;
		}
	}
	void UISlider::UpdatePercentage()
	{
		if (horizon_)
		{
			percentage_ = (slidebutton_pos.x - getPos().x) / getSize().w * 100.0f;
		}
		else
		{
			percentage_ = (slidebutton_pos.y - getPos().y) / getSize().h * 100.0f;
		}
	}
}
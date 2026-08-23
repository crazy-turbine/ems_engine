#pragma once
#include "UIButton.h"

namespace ems_engine
{
	class UISlider :public UIButton
	{
	public:
		UISlider() = default;
		UISlider(float x, float y, float w, float h, const std::vector<std::string>& visual_group, uint64_t slidebar_textureID, std::string_view state, float fps, uint64_t df_state, uint64_t hov_state, bool horizon, float percentage);
		UISlider(float x, float y, float w, float h, const std::vector<std::string>& visual_group, uint64_t slidebar_textureID, std::string_view state, float fps, std::string df_state, std::string hov_state, bool horizon, float percentage);

		void setPercentage(float percentage);
		float getPercentage();

		void setSlideButtonPos(float x, float y);
		Position getSlideButtonPos();

		void setHorizon(bool horizon);
		bool isHorizon();

		void setCurrentTextureID(uint64_t textureID, size_t index = 0) override;
		uint64_t getCurrentTextureID(size_t index) const override;
	private:
		void UpdateSlideButtonPos();
		void UpdatePercentage();
		uint64_t current_slidebar_textureID_ = 0;
		bool horizon_ = true;
		float percentage_ = 100.0f;
		Position slidebutton_pos = {0,0};
	};
}
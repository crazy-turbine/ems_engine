#pragma once
#include "UIButton.h"

namespace ems_engine
{
	class UICheckBox : public UIButton
	{
	public:
		UICheckBox();
		UICheckBox(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps, uint64_t df_state, uint64_t hov_state, uint64_t chk_state, uint64_t chk_hov_state);
		UICheckBox(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps, std::string df_state, std::string hov_state, std::string chk_state, std::string chk_hov_state = "");

		void setCheckedState(uint64_t state);
		void setCheckedHoverState(uint64_t state);
		void setCheckedState(std::string state);
		void setCheckedHoverState(std::string state);

		void setCheckOn(bool check_on);
		bool isCheckOn() const;

	private:
		uint64_t checked_state;
		uint64_t checked_hover_state;
		bool check = false;
	};
}
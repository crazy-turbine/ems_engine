#pragma once
#include "UIStateElement.h"

namespace ems_engine
{
	class UIButton :public UIStateElement
	{
	public:
		UIButton();
		UIButton(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps,uint64_t df_state,uint64_t hov_state);
		UIButton(float x, float y, float w, float h, const std::vector<std::string>& visual_group, std::string_view state, float fps, std::string df_state, std::string hov_state);
		
		bool contains(float mouseX,float mouseY);

		void setDefaultState(uint64_t state);
		void setHoverState(uint64_t state);
		void setDefaultState(std::string state);
		void setHoverState(std::string state);

		void setHoverOn(bool hover_on);

	protected:
		uint64_t default_state;
		uint64_t hover_state;
	};
}
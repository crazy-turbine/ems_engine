#pragma once
#include "UIStateElement.h"

namespace ems_engine
{
	class UIButton :public UIStateElement
	{
	public:
		bool contains(float mouseX,float mouseY);

		void setDefaultState(uint64_t state);
		void setHoverState(uint64_t state);
		void setDefaultState(std::string state);
		void setHoverState(std::string state);

		void setHoverOn(bool hover_on);

	private:
		uint64_t default_state;
		uint64_t hover_state;
	};
}
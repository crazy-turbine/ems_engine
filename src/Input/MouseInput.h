#pragma once
#include <vector>
#include <utility>

namespace ems_engine
{

	enum class mouse_code;
	enum class key_state;

	class MouseInput
	{
	public:
		bool UpdateState(std::vector <std::pair<mouse_code, key_state>>& key_list, float& x, float& y);
	private:
		uint32_t PrevState = 0;
		uint32_t CurrState = 0;
		mouse_code KeycodeConvert(uint8_t keynum);
	};
}

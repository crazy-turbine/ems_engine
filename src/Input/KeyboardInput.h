#pragma once
#include <vector>
#include <utility>

namespace ems_engine
{

	enum class keyboard_code;
	enum class key_state;

	class KeyboardInput
	{
	public:
		bool UpdateState(std::vector <std::pair<keyboard_code, key_state>>& key_list);
	private:
		std::vector<bool> PrevState;
		const bool* CurrState = nullptr;
		keyboard_code KeycodeConvert(int keynum);
	};
}

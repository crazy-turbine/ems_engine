#pragma once
#include <vector>

enum class keyboard_code;

class KeyboardInput
{
public:
	bool getState(std::vector<keyboard_code>& key_list);
private:
	keyboard_code KeycodeConvert(int keynum);
};
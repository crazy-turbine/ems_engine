#pragma once
#include <string>
#include "src/Common/enum.h"
#include <map>
#include <functional>

class SceneManager;
struct KeyboardConditionalKey;

class button_behavior
{
public:
	void ButtonExcute(keyboard_code code);
	void ButtonExcute(mouse_code code);
	void ButtonExcute(gamepad_code code);

	//void button_update();

	void setActionGroup(std::string group_name, std::function<void()> group_function);

	void setKeyboardConditionSelector(keyboard_code code, std::function<std::string()> selector);
	void setMouseConditionSelector(mouse_code code, std::function<std::string()> selector);
	void setGamepadConditionSelector(gamepad_code code, std::function<std::string()> selector);

	
	void setKeyboardActionGroup(keyboard_code code, std::string group_name, std::string condition);
	void setMouseActionGroup(mouse_code code, std::string group_name, std::string condition);
	void setGamepadActionGroup(gamepad_code code, std::string group_name, std::string condition);

private:
	void ActionExcute(std::string action);

	//std::map<keyboard_code, std::map<std::string, std::vector<std::string>>> Kaction_map;
	std::map<keyboard_code, std::function<std::vector<std::string>(key_state KeyState)>> Kaction_map;
	std::map<mouse_code, std::map<std::string, std::vector<std::string>>> Maction_map;
	std::map<gamepad_code, std::map<std::string, std::vector<std::string>>> Gaction_map;

	std::map<keyboard_code, std::function<std::string()>> Kcondition_map;
	std::map<mouse_code, std::function<std::string()>> Mcondition_map;
	std::map<gamepad_code, std::function<std::string()>> Gcondition_map;

	std::map<std::string, std::function<void()>> action_group;
};


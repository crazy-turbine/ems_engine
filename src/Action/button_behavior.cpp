#include "button_behavior.h"
#include "src/Resource/json.h"
#include "third_party/magic_enum/magic_enum.hpp"
#include "src/Scene/sceneManager.h"
#include "src/Resource/jsonManager.h"
#include "src/Action/Action.h"
#include <cmath>

void button_behavior::setActionGroup(std::string group_name, std::function<void()> group_function)
{
	action_group.insert_or_assign(group_name, group_function);
}
void button_behavior::setKeyboardConditionSelector(keyboard_code code, std::function<std::string()> selector)
{
	Kcondition_map.insert_or_assign(code, selector);
}
void button_behavior::setMouseConditionSelector(mouse_code code, std::function<std::string()> selector)
{
	Mcondition_map.insert_or_assign(code, selector);
}
void button_behavior::setGamepadConditionSelector(gamepad_code code, std::function<std::string()> selector)
{
	Gcondition_map.insert_or_assign(code, selector);
}
void button_behavior::setKeyboardActionGroup(keyboard_code code, std::string group_name, std::string condition)
{
	Kaction_map.at(code).at(condition) = group_name;
}
void button_behavior::setMouseActionGroup(mouse_code code, std::string group_name, std::string condition)
{
	Maction_map.at(code).at(condition) = group_name;
}
void button_behavior::setGamepadActionGroup(gamepad_code code, std::string group_name, std::string condition)
{
	if (auto it = Gaction_map.find(code); it != Gaction_map.end())
	{
		
	}
	else
	{
		std::cout << "[ERROR]: Function - ActionExcute : key \" "
			<< /*code <<*/ "\" not found !" << std::endl;
	}
	Gaction_map.at(code).at(condition) = group_name;
}
void button_behavior::ActionExcute(std::string action)
{
	if (auto it = action_group.find(action);it != action_group.end())
	{
		it->second();
	}
	else
	{
		std::cout << "[ERROR]: Function - ActionExcute : key \" "
			<< action << "\" not found !" << std::endl;
	}
}
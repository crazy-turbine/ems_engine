#include "button_behavior.h"
#include "src/Resource/json.h"
#include "third_party/magic_enum/magic_enum.hpp"
#include "src/Scene/sceneManager.h"
#include "src/Resource/jsonManager.h"
#include "src/Action/Action.h"
#include "src/Common/struct.h"
#include <cmath>

void button_behavior::ButtonExcute(keyboard_code code)
{
	auto itC = Kcondition_map.find(code);
	auto itA = Kaction_map.find(code);
	if (itC == Kcondition_map.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Kcondition_map : "
			<< "keyboard_code" << " not found !" << std::endl;
		return;
	}
	if (itA == Kaction_map.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Kaction_map : "
			<< "keyboard_code" << " not found !" << std::endl;
		return;
	}
	auto itN = itA->second.find(itC->second());
	if (itN == itA->second.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Kaction_map : "
			<< itC->second() << " not found !" << std::endl;
		return;
	}
	for (const auto& action : itN->second)
	{
		ActionExcute(action);
	}
}
void button_behavior::ButtonExcute(mouse_code code)
{
	auto itC = Mcondition_map.find(code);
	auto itA = Maction_map.find(code);
	if (itC == Mcondition_map.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Mcondition_map : "
			<< "mouse_code" << " not found !" << std::endl;
		return;
	}
	if (itA == Maction_map.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Maction_map : "
			<< itC->second() << " not found !" << std::endl;
		return;
	}
	auto itN = itA->second.find(itC->second());
	if (itN == itA->second.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Maction_map : "
			<< itC->second() << " not found !" << std::endl;
		return;
	}
	for (const auto& action : itN->second)
	{
		ActionExcute(action);
	}
}
void button_behavior::ButtonExcute(gamepad_code code)
{
	auto itC = Gcondition_map.find(code);
	auto itA = Gaction_map.find(code);
	if (itC == Gcondition_map.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Gcondition_map : "
			<< "keyboard_code" << " not found !" << std::endl;
		return;
	}
	if (itA == Gaction_map.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Gaction_map : "
			<< "keyboard_code" << " not found !" << std::endl;
		return;
	}
	auto itN = itA->second.find(itC->second());
	if (itN == itA->second.end())
	{
		std::cout << "[ERROR]: Function - ButtonExcute - Gaction_map : "
			<< itC->second() << " not found !" << std::endl;
		return;
	}
	for (const auto& action : itN->second)
	{
		ActionExcute(action);
	}
}
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
	auto [itC, itC_inserted] = Kaction_map.try_emplace(code);
	auto [itA, itA_inserted] = itC->second.try_emplace(condition);
	itA->second.push_back(group_name);
}
void button_behavior::setMouseActionGroup(mouse_code code, std::string group_name, std::string condition)
{
	auto [itC, itC_inserted] = Maction_map.try_emplace(code);
	auto [itA, itA_inserted] = itC->second.try_emplace(condition);
	itA->second.push_back(group_name);
}
void button_behavior::setGamepadActionGroup(gamepad_code code, std::string group_name, std::string condition)
{
	auto [itC, itC_inserted] = Gaction_map.try_emplace(code);
	auto [itA, itA_inserted] = itC->second.try_emplace(condition);
	itA->second.push_back(group_name);
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
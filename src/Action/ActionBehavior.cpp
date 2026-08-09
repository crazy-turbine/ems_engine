#include "ActionBehavior.h"
#include "src/Resource/json.h"
#include "ActionPolicyManager.h"
#include "ActionPolicy.h"
#include "third_party/magic_enum/magic_enum.hpp"
#include "src/Scene/sceneManager.h"
#include "src/Resource/jsonManager.h"
#include "src/Action/Action.h"
#include "src/Common/struct.h"
#include <cmath>

namespace ems_engine
{

	ActionBehavior::ActionBehavior(ActionPolicyManager* ap_manager)
	{
		action_policy_manager = ap_manager;
	}
	ActionBehavior::~ActionBehavior() = default;


	void ActionBehavior::ButtonExcute(const std::string& code)
	{
		std::vector<std::string> actionf =
			action_policy_manager->getActionPolicy(code)->getActionFlow();
		for (auto action_groupID : actionf)
		{
			ActionExcute(action_groupID);
		}

	}
	void ActionBehavior::ButtonExcute(keyboard_code code)
	{
		std::vector<std::string> actionf =
			action_policy_manager->getActionPolicy(code)->getActionFlow();
		for (auto action_groupID : actionf)
		{
			ActionExcute(action_groupID);
		}
	}
	void ActionBehavior::ButtonExcute(mouse_code code)
	{
		std::vector<std::string> actionf =
			action_policy_manager->getActionPolicy(code)->getActionFlow();
		for (auto action_groupID : actionf)
		{
			ActionExcute(action_groupID);
		}
	}
	void ActionBehavior::ButtonExcute(gamepad_code code)
	{
		std::vector<std::string> actionf =
			action_policy_manager->getActionPolicy(code)->getActionFlow();
		for (auto action_groupID : actionf)
		{
			ActionExcute(action_groupID);
		}
	}
	void ActionBehavior::setActionGroup(std::string group_name, std::function<void()> group_function)
	{
		action_group.insert_or_assign(group_name, group_function);
	}
	

	void ActionBehavior::setKeyboardActionGroup(keyboard_code code, std::string group_name, std::string condition)
	{
		auto [itC, itC_inserted] = Kaction_map.try_emplace(code);
		auto [itA, itA_inserted] = itC->second.try_emplace(condition);
		itA->second.push_back(group_name);
	}
	void ActionBehavior::setMouseActionGroup(mouse_code code, std::string group_name, std::string condition)
	{
		auto [itC, itC_inserted] = Maction_map.try_emplace(code);
		auto [itA, itA_inserted] = itC->second.try_emplace(condition);
		itA->second.push_back(group_name);
	}
	void ActionBehavior::setGamepadActionGroup(gamepad_code code, std::string group_name, std::string condition)
	{
		auto [itC, itC_inserted] = Gaction_map.try_emplace(code);
		auto [itA, itA_inserted] = itC->second.try_emplace(condition);
		itA->second.push_back(group_name);
	}
	void ActionBehavior::ActionExcute(std::string action_groupID)
	{
		if (auto it = action_group.find(action_groupID); it != action_group.end())
		{
			it->second();
		}
		else
		{
			std::cout << "[ERROR]: Function - ActionExcute : key \" "
				<< action_groupID << "\" not found !" << std::endl;
		}
	}
}

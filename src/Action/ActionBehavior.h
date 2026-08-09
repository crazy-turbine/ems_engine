#pragma once
#include <string>
#include "Common/enum.h"
#include <unordered_map>
#include <functional>
#include <memory>

namespace ems_engine
{

	class SceneManager;
	class ActionPolicyManager;
	struct KeyboardConditionalKey;

	class ActionBehavior
	{
	public:
		ActionBehavior(ActionPolicyManager* action_policy_manager);
		~ActionBehavior();

		void ButtonExcute(const std::string& code);
		void ButtonExcute(keyboard_code code);
		void ButtonExcute(mouse_code code);
		void ButtonExcute(gamepad_code code);

		//void button_update();

		void setActionGroup(std::string group_name, std::function<void()> group_function);

		

		
	private:
		void ActionExcute(std::string action_groupID);

		ActionPolicyManager* action_policy_manager;		
		std::unordered_map<std::string, std::function<void()>> action_group;
	};
}


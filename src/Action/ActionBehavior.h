#pragma once
#include <string>
#include "src/Common/enum.h"
#include <map>
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

		

		void addActionFlow(std::string code, std::string action_group_id, std::string condition);
		void addActionFlow(keyboard_code code, std::string action_group_id, std::string condition);
		void addActionFlow(mouse_code code, std::string action_group_id, std::string condition);
		void addActionFlow(gamepad_code code, std::string action_group_id, std::string condition);

	private:
		void ActionExcute(std::string action_groupID);

		//std::map<keyboard_code, std::map<std::string, std::vector<std::string>>> Kaction_map;
		/*std::map<keyboard_code, std::function<std::vector<std::string>(key_state KeyState)>> Kaction_map;
		std::map<mouse_code, std::map<std::string, std::vector<std::string>>> Maction_map;
		std::map<gamepad_code, std::map<std::string, std::vector<std::string>>> Gaction_map;

		std::map<keyboard_code, std::function<std::string()>> Kcondition_map;
		std::map<mouse_code, std::function<std::string()>> Mcondition_map;
		std::map<gamepad_code, std::function<std::string()>> Gcondition_map;*/
		ActionPolicyManager* action_policy_manager;
		
		std::map<std::string, std::function<void()>> action_group;
	};
}


#pragma once
#include <string>
#include <functional>
#include "InputCode.h"

namespace ems_engine
{
	class ActionPolicyManager;
	class ActionBehavior;
	class ActionAPI
	{
	public:
		ActionAPI(ActionPolicyManager* ap_mgr, ActionBehavior* action_be);

		//ActionBehavior
		void setActionGroup(std::string action_group_id, std::function<void()> group_function);


		//APM
		bool createActionPolicy(const std::string& key);
		bool createActionPolicy(const keyboard_code& key);
		bool createActionPolicy(const mouse_code& key);
		bool createActionPolicy(const gamepad_code& key);

		void setConditionSelector(std::string code, std::function<std::string()> selector);
		void setConditionSelector(keyboard_code code, std::function<std::string()> selector);
		void setConditionSelector(mouse_code code, std::function<std::string()> selector);
		void setConditionSelector(gamepad_code code, std::function<std::string()> selector);

		void addActionGroupIdToActionFlow(std::string code, std::string action_group_id, std::string condition);
		void addActionGroupIdToActionFlow(keyboard_code code, std::string action_group_id, std::string condition);
		void addActionGroupIdToActionFlow(mouse_code code, std::string action_group_id, std::string condition);
		void addActionGroupIdToActionFlow(gamepad_code code, std::string action_group_id, std::string condition);

		void addActionGroupIdToActionFlow(std::string code, std::string action_group_id);
		void addActionGroupIdToActionFlow(keyboard_code code, std::string action_group_id);
		void addActionGroupIdToActionFlow(mouse_code code, std::string action_group_id);
		void addActionGroupIdToActionFlow(gamepad_code code, std::string action_group_id);

	private:
		ActionPolicyManager* ap_mgr_;
		ActionBehavior* action_be_;
	};
}
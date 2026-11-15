#pragma once
#include <unordered_map>
#include <string>
#include <functional>
#include <memory>

namespace ems_engine
{
	class ActionPolicy;
	struct ActionPolicyConfig;
	enum class keyboard_code;
	enum class mouse_code;
	enum class gamepad_code;

	class ActionPolicyManager
	{
	public:
		ActionPolicyManager();
		~ActionPolicyManager();
		bool createActionPolicy(const std::string& key);
		bool createActionPolicy(const keyboard_code& key);
		bool createActionPolicy(const mouse_code& key);
		bool createActionPolicy(const gamepad_code& key);
		ActionPolicy* getActionPolicy(const std::string& key);
		ActionPolicy* getActionPolicy(const keyboard_code& key);
		ActionPolicy* getActionPolicy(const mouse_code& key);
		ActionPolicy* getActionPolicy(const gamepad_code& key);

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
		bool ActionPolicyCreater(const uint64_t& hash);
		ActionPolicy* ActionPolicyGetter(const uint64_t& hash);
		std::unordered_map<uint64_t, std::unique_ptr<ActionPolicy>> ActionPolicyList;
	};
};

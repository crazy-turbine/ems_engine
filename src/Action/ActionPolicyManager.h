#pragma once
#include<unordered_map>
#include<string>

namespace ems_engine
{
	class ActionPolicy;
	struct ActionPolicyConfig;
	enum keyboard_code;
	enum mouse_code;
	enum gamepad_code;

	class ActionPolicyManager
	{
	public:

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



	private:
		bool ActionPolicyCreater(const uint64_t& hash);
		ActionPolicy* ActionPolicyGetter(const uint64_t& hash);
		std::unordered_map<uint64_t, ActionPolicy> ActionPolicyList;
	};
};

#include "ActionPolicy.h"
#include <iostream>

namespace ems_engine
{

	void ActionPolicy::setActionFlow(const std::string& conditionID, const actionf& action_flow)
	{
		ActionExecuteMap.insert_or_assign(conditionID, action_flow);
	}
	void ActionPolicy::addActionGroupID(const std::string& conditionID, const std::string& action_group_id)
	{
		auto [it, inserted] = ActionExecuteMap.try_emplace(conditionID);
		it->second.push_back(action_group_id);
	}
	void ActionPolicy::setActionFlow(const actionf& action_flow)
	{
		setActionFlow("", action_flow);
	}
	void ActionPolicy::addActionGroupID(const std::string& action_group_id)
	{
		addActionGroupID("", action_group_id);
	}

	void ActionPolicy::setConditionSelector(std::function<std::string()> condition_selector)
	{
		ConditionSelector = condition_selector;
	}
	std::string ActionPolicy::getConditionID() const
	{
		if (ConditionSelector)
		{
			return ConditionSelector();
		}
		else
		{
			return "";
		}
	}
	const ActionPolicy::actionf& ActionPolicy::getActionFlow()
	{
		static const actionf empty_vector;
		std::string conditionID = getConditionID();
		auto it = ActionExecuteMap.find(conditionID);
		if (it != ActionExecuteMap.end())
		{
			return it->second;
		}
		else
		{
			std::cout<<"[Debug]:ActionFlow Not Found"
			return empty_vector;
		}
	}
}

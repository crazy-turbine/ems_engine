#pragma once
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>


class ActionPolicy
{
private:
	using actionf = std::vector<std::string>;


public:
	void setActionFlow(const std::string& conditionID, const actionf& action_flow);
	void addActionGroupID(const std::string& conditionID, const std::string& action_group_id);
	void setActionFlow(const actionf& action_flow);
	void addActionGroupID(const std::string& action_group_id);
	void setConditionSelector(std::function<std::string()> condition_selector);
	std::string getConditionID() const;

private:
	//動作執行條件選擇器
	std::function<std::string()> ConditionSelector;
	//<(std::string)條件,(std::vector)動作流程組<動作組ID>> 動作執行列表
	std::unordered_map<std::string, actionf> ActionExecuteMap;
};
#pragma once
#include <vector>
#include <string>

class BehaviorConditionSelector
{
public:

	void setActionList(std::string action_name);
	const std::vector<std::string>& getActionList();
protected:
	std::vector<std::string> action_list;
};
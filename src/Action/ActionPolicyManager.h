#pragma once
#include<unordered_map>

class ActionPolicy;

class ActionPolicyManager
{
public:
	void createActionPolicy()
	{

	}
private:
	std::unordered_map<uint64_t, ActionPolicy> ActionPolicyList;
};
#include "ActionPolicyManager.h"
#include "ActionPolicy.h"
#include "Common/struct.h"
#include "Common/enum.h"
#include "Common/toHash.h"
#include <iostream>
namespace ems_engine
{
	ActionPolicyManager::ActionPolicyManager() = default;
	ActionPolicyManager::~ActionPolicyManager() = default;

	bool ActionPolicyManager::createActionPolicy(const std::string& key)
	{
		uint64_t hash_key = string_toHash(key);
		return ActionPolicyCreater(hash_key);
	}

	bool ActionPolicyManager::createActionPolicy(const keyboard_code& key)
	{
		uint64_t hash_key = enum_toHash(key);
		return ActionPolicyCreater(hash_key);
	}
	bool ActionPolicyManager::createActionPolicy(const mouse_code& key)
	{
		uint64_t hash_key = enum_toHash(key);
		return ActionPolicyCreater(hash_key);
	}
	bool ActionPolicyManager::createActionPolicy(const gamepad_code& key)
	{
		uint64_t hash_key = enum_toHash(key);
		return ActionPolicyCreater(hash_key);
	}
	bool ActionPolicyManager::ActionPolicyCreater(const uint64_t& hash)
	{
		if (!ActionPolicyList.try_emplace(hash,std::make_unique<ActionPolicy>()).second)
		{
			std::cout << "[Debug]:ActionPolicy already exists!" << std::endl;
			return false;
		}
		else
			return true;
	}
	ActionPolicy* ActionPolicyManager::getActionPolicy(const std::string& key)
	{
		uint64_t hash_key = string_toHash(key);
		return ActionPolicyGetter(hash_key);
	}
	ActionPolicy* ActionPolicyManager::getActionPolicy(const keyboard_code& key)
	{
		uint64_t hash_key = enum_toHash(key);
		return ActionPolicyGetter(hash_key);
	}
	ActionPolicy* ActionPolicyManager::getActionPolicy(const mouse_code& key)
	{
		uint64_t hash_key = enum_toHash(key);
		return ActionPolicyGetter(hash_key);
	}
	ActionPolicy* ActionPolicyManager::getActionPolicy(const gamepad_code& key)
	{
		uint64_t hash_key = enum_toHash(key);
		return ActionPolicyGetter(hash_key);
	}

	void ActionPolicyManager::setConditionSelector(std::string code, std::function<std::string()> selector)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->setConditionSelector(selector);
	}
	void ActionPolicyManager::setConditionSelector(keyboard_code code, std::function<std::string()> selector)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->setConditionSelector(selector);
	}
	void ActionPolicyManager::setConditionSelector(mouse_code code, std::function<std::string()> selector)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->setConditionSelector(selector);
	}
	void ActionPolicyManager::setConditionSelector(gamepad_code code, std::function<std::string()> selector)
	{
		auto AP = getActionPolicy(code);
		if(AP!=nullptr)
			AP->setConditionSelector(selector);
	}


	void ActionPolicyManager::addActionGroupID(std::string code, std::string group_name, std::string condition)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->addActionGroupID(condition, group_name);
	}
	void ActionPolicyManager::addActionGroupID(keyboard_code code, std::string group_name, std::string condition)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->addActionGroupID(condition, group_name);
	}
	void ActionPolicyManager::addActionGroupID(mouse_code code, std::string group_name, std::string condition)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->addActionGroupID(condition, group_name);
	}
	void ActionPolicyManager::addActionGroupID(gamepad_code code, std::string group_name, std::string condition)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->addActionGroupID(condition, group_name);
	}


	void ActionPolicyManager::addActionGroupID(std::string code, std::string group_name)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->addActionGroupID(group_name);
	}
	void ActionPolicyManager::addActionGroupID(keyboard_code code, std::string group_name)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->addActionGroupID(group_name);
	}
	void ActionPolicyManager::addActionGroupID(mouse_code code, std::string group_name)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->addActionGroupID(group_name);
	}
	void ActionPolicyManager::addActionGroupID(gamepad_code code, std::string group_name)
	{
		auto AP = getActionPolicy(code);
		if (AP != nullptr)
			AP->addActionGroupID(group_name);
	}

	ActionPolicy* ActionPolicyManager::ActionPolicyGetter(const uint64_t& hash)
	{
		auto it = ActionPolicyList.find(hash);
		if (it == ActionPolicyList.end())
		{
			std::cout << "[Debug]:ActionPolicy not found" << std::endl;
			return nullptr;
		}
		else
			return it->second.get();
	}
};
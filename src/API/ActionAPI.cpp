#include "include/ems_engine/ActionAPI.h"
#include "Action/ActionPolicyManager.h";
#include "Action/ActionBehavior.h";

namespace ems_engine
{
	ActionAPI::ActionAPI(ActionPolicyManager* ap_mgr, ActionBehavior* action_be)
	{
		ap_mgr_ = ap_mgr;
		action_be_ = action_be;
	}
	void ActionAPI::setActionGroup(std::string group_name, std::function<void()> group_function)
	{
		action_be_->setActionGroup(group_name, group_function);
	}

	//APM
	bool ActionAPI::createActionPolicy(const std::string& key)
	{
		return ap_mgr_->createActionPolicy(key);
	}
	bool ActionAPI::createActionPolicy(const keyboard_code& key)
	{
		return ap_mgr_->createActionPolicy(key);
	}
	bool ActionAPI::createActionPolicy(const mouse_code& key)
	{
		return ap_mgr_->createActionPolicy(key);
	}
	bool ActionAPI::createActionPolicy(const gamepad_code& key)
	{
		return ap_mgr_->createActionPolicy(key);
	}
	//ActionPolicy* getActionPolicy(const std::string& key);
	//ActionPolicy* getActionPolicy(const keyboard_code& key);
	//ActionPolicy* getActionPolicy(const mouse_code& key);
	//ActionPolicy* getActionPolicy(const gamepad_code& key);

	void ActionAPI::setConditionSelector(std::string code, std::function<std::string()> selector)
	{
		ap_mgr_->setConditionSelector(code, selector);
	}
	void ActionAPI::setConditionSelector(keyboard_code code, std::function<std::string()> selector)
	{
		ap_mgr_->setConditionSelector(code, selector);
	}
	void ActionAPI::setConditionSelector(mouse_code code, std::function<std::string()> selector)
	{
		ap_mgr_->setConditionSelector(code, selector);
	}
	void ActionAPI::setConditionSelector(gamepad_code code, std::function<std::string()> selector)
	{
		ap_mgr_->setConditionSelector(code, selector);
	}

	void ActionAPI::addActionGroupID(std::string code, std::string action_group_id, std::string condition)
	{
		ap_mgr_->addActionGroupID(code, action_group_id, condition);
	}
	void ActionAPI::addActionGroupID(keyboard_code code, std::string action_group_id, std::string condition)
	{
		ap_mgr_->addActionGroupID(code, action_group_id, condition);
	}
	void ActionAPI::addActionGroupID(mouse_code code, std::string action_group_id, std::string condition)
	{
		ap_mgr_->addActionGroupID(code, action_group_id, condition);
	}
	void ActionAPI::addActionGroupID(gamepad_code code, std::string action_group_id, std::string condition)
	{
		ap_mgr_->addActionGroupID(code, action_group_id, condition);
	}

	void ActionAPI::addActionGroupID(std::string code, std::string action_group_id)
	{
		ap_mgr_->addActionGroupID(code, action_group_id);
	}
	void ActionAPI::addActionGroupID(keyboard_code code, std::string action_group_id)
	{
		ap_mgr_->addActionGroupID(code, action_group_id);
	}
	void ActionAPI::addActionGroupID(mouse_code code, std::string action_group_id)
	{
		ap_mgr_->addActionGroupID(code, action_group_id);
	}
	void ActionAPI::addActionGroupID(gamepad_code code, std::string action_group_id)
	{
		ap_mgr_->addActionGroupID(code, action_group_id);
	}

}

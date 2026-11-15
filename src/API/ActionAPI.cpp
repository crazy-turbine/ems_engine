#include <stdexcept>

#include "include/ems_engine/ActionAPI.h"
#include "Action/ActionPolicyManager.h";
#include "Action/ActionBehavior.h";

namespace ems_engine
{
	ActionAPI::ActionAPI(ActionPolicyManager* ap_mgr, ActionBehavior* action_be)
		:ap_mgr_(ap_mgr),action_be_(action_be)
	{
		if (ap_mgr_ == nullptr)
			throw std::invalid_argument("ActionPolicyManager is nullptr!");
		if (action_be_ == nullptr)
			throw std::invalid_argument("ActionBehavior is nullptr!");
	}
	void ActionAPI::setActionGroup(std::string action_group_id, std::function<void()> group_function)
	{
		action_be_->setActionGroup(action_group_id, group_function);
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

	void ActionAPI::addActionGroupIdToActionFlow(std::string code, std::string action_group_id, std::string condition)
	{
		ap_mgr_->addActionGroupIdToActionFlow(code, action_group_id, condition);
	}
	void ActionAPI::addActionGroupIdToActionFlow(keyboard_code code, std::string action_group_id, std::string condition)
	{
		ap_mgr_->addActionGroupIdToActionFlow(code, action_group_id, condition);
	}
	void ActionAPI::addActionGroupIdToActionFlow(mouse_code code, std::string action_group_id, std::string condition)
	{
		ap_mgr_->addActionGroupIdToActionFlow(code, action_group_id, condition);
	}
	void ActionAPI::addActionGroupIdToActionFlow(gamepad_code code, std::string action_group_id, std::string condition)
	{
		ap_mgr_->addActionGroupIdToActionFlow(code, action_group_id, condition);
	}

	void ActionAPI::addActionGroupIdToActionFlow(std::string code, std::string action_group_id)
	{
		ap_mgr_->addActionGroupIdToActionFlow(code, action_group_id);
	}
	void ActionAPI::addActionGroupIdToActionFlow(keyboard_code code, std::string action_group_id)
	{
		ap_mgr_->addActionGroupIdToActionFlow(code, action_group_id);
	}
	void ActionAPI::addActionGroupIdToActionFlow(mouse_code code, std::string action_group_id)
	{
		ap_mgr_->addActionGroupIdToActionFlow(code, action_group_id);
	}
	void ActionAPI::addActionGroupIdToActionFlow(gamepad_code code, std::string action_group_id)
	{
		ap_mgr_->addActionGroupIdToActionFlow(code, action_group_id);
	}

}

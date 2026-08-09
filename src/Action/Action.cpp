#include "Action.h"
#include "src/Common/struct.h"
#include "src/Resource/jsonManager.h"
#include "src/Output/Render.h"
#include "src/Scene/SceneManager.h"
#include "src/Common/JsonValue.h"
#include <algorithm>

namespace ems_engine
{

	EngineAction::EngineAction(Render* wd, EngineState* e_state, SceneManager* uim)
	{
		state = e_state;
		uiMgr = uim;
		window = wd;
	}

	void EngineAction::delSlot(int series)
	{
		json default_slot;
		JsonManager::addJson("saves/save_list.json");
		json& savelist = JsonManager::getJson("saves/save_list.json");
		std::string s_ptr = "/slot/" + std::to_string(series - 1);
		json::json_pointer ptr(s_ptr);
		readJson(savelist, "/Default"_json_pointer, default_slot);
		writeJson(savelist, ptr, default_slot);
		saveJson(savelist, "saves/save_list.json");
	}
	void EngineAction::coverSlot(int series)
	{
		delSlot(series);
		json& savelist = JsonManager::getJson("saves/save_list.json");
		std::string s_ptr = "/slot/" + std::to_string(series - 1);
		json::json_pointer ptr(s_ptr + "/isCreated");
		bool isCreated = true;
		writeJson(savelist, ptr, isCreated);
	}
	void EngineAction::setLang(std::string lang)
	{
		state->Language = lang;
	}
	void EngineAction::setTargetScene(std::string tar_scene)
	{
		uiMgr->setTargetSceneID(tar_scene);
	}
	void EngineAction::dragButton(Entity* button)
	{
		state->isDragging = true;
		state->TargetButton = button;
	}
	void EngineAction::clickBar(Entity* button)
	{
		state->isDragging = true;
		state->TargetButton = uiMgr->getCurrentScene()->getEntity
		("slide_button", button->getSlideButton());
	}
	void EngineAction::RefreshDrag(Entity* button)
	{
		bool toggle = false;
		float value = 0.0f;
		std::string actionID = button->getAction();
		if (state->isDragging)
		{
			if (state->TargetButton == button)
			{
				state->volume = (1000 - (button->getOriginalPos().x - std::clamp(state->mouseX, button->getOriginalPos().x - 1000.0f, button->getOriginalPos().x))) / 10.0f;
			}
			if (state->TargetButton == nullptr)
				std::cout << "[ERROR]:Slide_button is nullptr" << std::endl;
		}
		value = state->volume * 10.0f;
		button->setPos
		(
			button->getOriginalPos().x - (1000.0f - value),
			button->getPos().y
		);
	}
	void EngineAction::setVsync(bool toggle)
	{
		state->Vsync = toggle;
		window->Vsync(state->Vsync);
	}
	void EngineAction::setFullscreen(bool toggle)
	{
		state->fullscreen = toggle;
		window->fullscreen(state->fullscreen);
	}
	void EngineAction::setMousegrab(bool toggle)
	{
		state->mouseGrab = toggle;
		window->mousegrab(state->mouseGrab);
	}
	void EngineAction::saveSetting(std::vector<std::pair<json::json_pointer, JsonValue>> option_list)
	{
		for (auto& option : option_list)
		{
			writeJson(JsonManager::getJson("res/setting/setting.json"), option.first, option.second);
		}
	}
	void EngineAction::RefreshText()
	{
		state->isRefreshText = true;
	}
}

#pragma once
#include <string>
#include <vector>
#include"src/Resource/json.h"

namespace ems_engine
{

	struct EngineState;
	class SceneManager;
	class Entity;
	class Render;
	class JsonValue;


	class EngineAction
	{
	public:
		EngineAction(Render* wd, EngineState* e_state, SceneManager* uim);
		void delSlot(int series);
		void coverSlot(int series);
		void setLang(std::string lang);
		void setTargetScene(std::string tar_scene);
		void dragButton(Entity* button);
		void clickBar(Entity* button);
		void RefreshDrag(Entity* button);
		void setVsync(bool toggle);
		void setFullscreen(bool toggle);
		void setMousegrab(bool toggle);
		void saveSetting(std::vector<std::pair<json::json_pointer, JsonValue>> option_list);
		void RefreshText();
	private:
		EngineState* state;
		SceneManager* uiMgr;
		Render* window;
	};
}

//void delSlot(int series);
//void coverSlot(int series);
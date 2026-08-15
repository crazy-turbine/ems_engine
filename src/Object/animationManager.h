#pragma once
//#include "src/Gameplay/Create.h"

namespace ems_engine
{
	enum class scene_ani_state;
	class SceneManager;

	bool scene_animationIN(scene_ani_state& state, SceneManager& uiManager);
	bool scene_animationOUT(scene_ani_state& state, SceneManager& uiManager);
	bool intro_animationIN(bool& intro, SceneManager& uiManager);
}

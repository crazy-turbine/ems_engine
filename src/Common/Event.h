#pragma once
#include <SDL3/SDL.h>
#include "src/Output/Render.h"
#include "src/Common/enum.h"
#include "src/Scene/sceneManager.h"

namespace ems_engine
{
	class audio;

	void EngineEvent(const SDL_Event& event, Render& window, SceneManager& uiManager, EngineState& state, scene_ani_state& aniState, audio& sound_sys);
	//void home_SDLevent(const SDL_Event& event, Render& window, bool& app, bool& home);
}

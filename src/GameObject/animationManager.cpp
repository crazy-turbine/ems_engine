#include "animationManager.h"
#include "src/Timer/timerManager.h"

bool scene_animationIN(scene_ani_state& state, SceneManager& uiManager)
{
	if(state == scene_ani_state::aniIN)
	{
		createTimer("scene_animationIN", 1);
		//std::cout << "pixel:" << animation.w << "x" << animation.h << std::endl;
		if (!TimerMap["scene_animationIN"]->checkTime())
		{
			float x = std::lerp(3840.0f, -1920.0f, TimerMap["scene_animationIN"]->getEasedProgress());
			float y = uiManager.getGlobalScene()->getEntity(entity_type::object, "animation")->getPos().y;
			//std::cout << "[IN] animation set position" << std::endl;
			//std::cout << "setup:" << ani.x << "," << ani.y << std::endl;
			uiManager.getGlobalScene()->getEntity(entity_type::object, "animation")->setPos(x, y);
			return true;
		}
		else
		{
			float x = -3840.0f;
			float y = uiManager.getGlobalScene()->getEntity(entity_type::object,"animation")->getPos().y;
			uiManager.getGlobalScene()->getEntity(entity_type::object, "animation")->setPos(x, y);
			deleteTimer("scene_animationIN");
			state = scene_ani_state::aniOUT;
			return false;
		}
	}
	else
	{
		deleteTimer("scene_animationIN");
	}
}
bool scene_animationOUT(scene_ani_state& state, SceneManager& uiManager)
{
	if (state == scene_ani_state::aniOUT)
	{
		createTimer("scene_animationOUT", 1);
		if (!TimerMap["scene_animationOUT"]->checkTime())
		{
			float x = std::lerp(-1920.0f, 3840.0f, TimerMap["scene_animationOUT"]->getEasedProgress());
			float y = uiManager.getGlobalScene()->getEntity(entity_type::object, "animation")->getPos().y;
			//std::cout << "[OUT] animation set position" << std::endl;
			//std::cout << "home:" << ani.x << "," << ani.y << std::endl;
			uiManager.getGlobalScene()->getEntity(entity_type::object, "animation")->setPos(x, y);
			return true;
		}
		else
		{
			float x = 3840.0f;
			float y = uiManager.getGlobalScene()->getEntity(entity_type::object, "animation")->getPos().y;
			uiManager.getGlobalScene()->getEntity(entity_type::object, "animation")->setPos(x, y);
			deleteTimer("scene_animationOUT");
			state = scene_ani_state::None;
			return false;
		}
	}
	else
	{
		deleteTimer("scene_animationOUT");
	}
}

bool intro_animationIN(bool &intro, SceneManager& uiManager)
{
	if (!intro || uiManager.getSceneID() != scene_ID::home)
		return false;
	if (createTimer("intro_animation_wait", 1.5))
	{
		uiManager.getCurrentScene()->eachEntity
		(
			[&](Entity* entity , std::string key)
			{
				if (key != "home_shadow" && key != "home_ADOF_Logo")
					entity->setAlpha(0);
				if (key == "home_ADOF_Logo")
				{
					entity->setPos(640, 360);
					entity->CurrentFrame(2560, 1440);
				}
			}

		);
		uiManager.getCurrentScene()->eachText
		(
			[&](ttf* t, std::string key)
			{
				t->setAlpha(0);
			}

		);
	}
	if (TimerMap["intro_animation_wait"]->checkTime())
	{
		createTimer("intro_animation", 1);
		if (!TimerMap["intro_animation"]->checkTime())
		{
			uiManager.getCurrentScene()->eachEntity
			(
				[&](Entity* entity, std::string key)
				{
					if (key != "home_shadow" && key != "home_ADOF_Logo")
					{
						entity->setAlpha(std::lerp(0, 255, TimerMap["intro_animation"]->getEasedProgress()));
					}
					if (key == "home_ADOF_Logo")
					{
						entity->CurrentFrame(std::lerp(2560, 1920, TimerMap["intro_animation"]->getEasedProgress()), std::lerp(1440, 1080, TimerMap["intro_animation"]->getEasedProgress()));
						entity->setPos((3840 - entity->getCurrentFrame().w) / 2, std::lerp(360, -230, TimerMap["intro_animation"]->getEasedProgress()));
					}
				}

			);
			uiManager.getCurrentScene()->eachText
			(
				[&](ttf* t, std::string key)
				{
					t->setAlpha(std::lerp(0, 255, TimerMap["intro_animation"]->getEasedProgress()));
				}

			);
			return true;
		}
		else
		{
			uiManager.getCurrentScene()->eachEntity
			(
				[&](Entity* entity, std::string key)
				{
					entity->setAlpha(255);
					if (key == "home_ADOF_Logo")
					{
						entity->CurrentFrame(1920, 1080);
						entity->setPos((3840 - entity->getCurrentFrame().w) / 2, -230);
					}
				}
			);
			uiManager.getCurrentScene()->eachText
			(
				[&](ttf* t, std::string key)
				{
					t->setAlpha(255);
				}
			);
			deleteTimer("intro_animation");
			deleteTimer("intro_animation_wait");
			intro = false;
			return false;
		}
	}
}
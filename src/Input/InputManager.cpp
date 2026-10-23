#include "InputManager.h"
#include "KeyboardInput.h"
#include "MouseInput.h"
#include "src/Common/enum.h"
#include "src/Action/ActionBehavior.h"
#include "include/ems_engine/Object/UIElement/UIButton.h"
#include "Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "Output/Render.h"
#include <vector>

namespace ems_engine
{

	InputManager::InputManager(ActionBehavior* bh, SceneManager* sc_mgr, Render* render)
	{
		a_bh = bh;
		scene_mgr = sc_mgr;
		render_sys = render;
		Kinput = std::make_unique<KeyboardInput>();
		Minput = std::make_unique<MouseInput>();
		//Ginput = std::make_unique<GamepadInput>();
		//Tinput = std::make_unique<TouchInput>();
	}
	InputManager::~InputManager() = default;
	void InputManager::InputRefresh()
	{
		std::vector<std::pair<keyboard_code, key_state>> Klist;
		std::vector<std::pair<mouse_code, key_state>> Mlist;
		if (Kinput->UpdateState(Klist))
		{
			for (const auto Key : Klist)
			{
				a_bh->ButtonExcute(Key.first);
			}
		}
		float MouseX, MouseY;
		Minput->UpdateState(Mlist, MouseX, MouseY);
		if (render_sys != nullptr)
		{
			float logicalMouseX, logicalMouseY;
			SDL_RenderCoordinatesFromWindow
			(
				render_sys->getRenderer(),
				MouseX, MouseY,
				&logicalMouseX, &logicalMouseY
			);
			MouseX = logicalMouseX;
			MouseY = logicalMouseY;
		}
		{
			bool left_down = false;
			key_state left_state;
			for (const auto Key : Mlist)
			{
				a_bh->ButtonExcute(Key.first);
				if (Key.first == mouse_code::Left)
				{
					left_down = true;
					left_state = Key.second;
					
				}
			}
			scene_mgr->getCurrentScene()->ExecuteOneTypeObject<UIButton>
				(
					[&](UIButton* button, std::string key)
					{
						if (button->contains(MouseX, MouseY))
						{
							button->setHoverOn(true);
							std::cout << "[DEBUG]: " << key << "Hover ON" << std::endl;
							if (left_state == key_state::down)
							{
								click_down_objID = key;
							}
							if (left_state == key_state::up)
							{
								click_up_objID = key;
							}
						}
						else
						{
							button->setHoverOn(false);
							//std::cout << "[DEBUG]: " << key << "Hover OFF" << std::endl;
						}
					}
				);
			if (!click_up_objID.empty() && click_up_objID == click_down_objID)
			{
				a_bh->ButtonExcute(click_up_objID);
				click_down_objID = "";
				click_up_objID = "";
			}
			if (!left_down)
			{
				click_down_objID = "";
				click_up_objID = "";
			}

		}
	}
}

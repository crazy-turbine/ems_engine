#include "src/Resource/jsonManager.h"
#include "Event.h"
#include "src/Object/entity.h"
#include "src/Object/Create.h"
#include "src/Output/RenderManager.h"
#include "src/Output/Audio.h"
#include <iostream>

namespace ems_engine
{

    void EngineEvent(const SDL_Event& event, Render& window, SceneManager& uiManager)
    {

        if (event.type == SDL_EVENT_QUIT)
        {
            uiManager.setTargetSceneID("game_exit");
        }

        

 /*
        if (event.type == SDL_EVENT_MOUSE_MOTION)
        {
           
            SDL_RenderCoordinatesFromWindow(window.getRenderer(), event.motion.x, event.motion.y, &state.mouseX, &state.mouseY);
            uiManager.getCurrentScene()->OneEntityMap
            (
                "dynamic_back",
                [&](Entity* back)
                {
                    float targetX = state.mouseX * -1 / 20;
                    float targetY = state.mouseY * -1 / 20;

                    if (!SDL_GetWindowMouseGrab(window.getSDLWindow()))
                        back->setPos(std::lerp(back->getPos().x, targetX, 0.1f), std::lerp(back->getPos().y, targetY, 0.1f));
                    else
                        back->setPos(targetX, targetY);
                    //std::cout << "[DEBUG]:Back Pos:" << back->getPos().x << "/" << back->getPos().y << std::endl;
                    //std::cout << "[DEBUG]:Mouse Pos:" << mouseX << "/" << mouseY << std::endl;
                }
            );
            uiManager.getCurrentScene()->OneEntityMap
            (
                "button",
                [&](Entity* button)
                {
                    if (button->isVisible() &&
                        state.mouseX >= button->getPos().x &&
                        state.mouseX <= button->getPos().x + button->getCurrentFrame().w &&
                        state.mouseY >= button->getPos().y &&
                        state.mouseY <= button->getPos().y + button->getCurrentFrame().h)
                    {
                        button->setTex_num(2);
                    }
                    else
                    {
                        button->setTex_num(1);
                    }
                }
            );
            uiManager.getCurrentScene()->OneEntityMap
            (
                "select_button",
                [&](Entity* button)
                {
                    if (button->isVisible() &&
                        state.mouseX >= button->getPos().x &&
                        state.mouseX <= button->getPos().x + button->getCurrentFrame().w &&
                        state.mouseY >= button->getPos().y &&
                        state.mouseY <= button->getPos().y + button->getCurrentFrame().h)
                    {
                        if (button->getTex_num() == 1)
                            button->setTex_num(2);
                        if (button->getTex_num() == 3)
                            button->setTex_num(4);
                    }
                    else
                    {
                        if (button->getTex_num() == 2)
                            button->setTex_num(1);
                        if (button->getTex_num() == 4)
                            button->setTex_num(3);
                    }
                }
            );

            uiManager.getCurrentScene()->OneEntityMap
            (
                "slide_button",
                [&](Entity* button, std::string key)
                {
                    if (button->isVisible() &&
                        state.mouseX >= button->getPos().x &&
                        state.mouseX <= button->getPos().x + button->getCurrentFrame().w &&
                        state.mouseY >= button->getPos().y &&
                        state.mouseY <= button->getPos().y + button->getCurrentFrame().h)
                    {
                        button->setTex_num(2);
                    }
                    else
                    {
                        button->setTex_num(1);
                    }
                }
            );
        }

        if (aniState != scene_ani_state::aniIN)
        {

            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN)
            {
                float mouseX = state.mouseX;
                float mouseY = state.mouseY;
                //mouseX = std::clamp(state.mouseX, 0.0f, 3840.0f);
                //mouseY = std::clamp(state.mouseY, 0.0f, 2160.0f);
                uiManager.getCurrentScene()->OneEntityMap
                (
                    "button",
                    [&](Entity* button, std::string key)
                    {
                        if (button->isVisible() &&
                            mouseX >= button->getPos().x &&
                            mouseX <= button->getPos().x + button->getCurrentFrame().w &&
                            mouseY >= button->getPos().y &&
                            mouseY <= button->getPos().y + button->getCurrentFrame().h)
                        {
                            sound_sys.playButtonSound();
                            button_action(window, uiManager, button, config, state);
                        }
                    }
                );
                uiManager.getCurrentScene()->OneEntityMap
                (
                    "select_button",
                    [&](Entity* button)
                    {
                        if (button->isVisible() &&
                            mouseX >= button->getPos().x &&
                            mouseX <= button->getPos().x + button->getCurrentFrame().w &&
                            mouseY >= button->getPos().y &&
                            mouseY <= button->getPos().y + button->getCurrentFrame().h)
                        {
                            sound_sys.playButtonSound();
                            button_action(window, uiManager, button, config, state);
                        }
                    }
                );
                uiManager.getCurrentScene()->OneEntityMap
                (
                    "slide_bar",
                    [&](Entity* button)
                    {
                        if (button->isVisible() &&
                            mouseX >= button->getPos().x &&
                            mouseX <= button->getPos().x + button->getCurrentFrame().w &&
                            mouseY >= button->getPos().y &&
                            mouseY <= button->getPos().y + button->getCurrentFrame().h)
                        {
                            sound_sys.playButtonSound();
                            button_action(window, uiManager, button, config, state);
                        }
                    }
                );
                // state.TargetButton = nullptr;
                 //state.isDragging = false;
                uiManager.getCurrentScene()->OneEntityMap
                (
                    "slide_button",
                    [&](Entity* button)
                    {
                        if (button->isVisible() &&
                            mouseX >= button->getPos().x &&
                            mouseX <= button->getPos().x + button->getCurrentFrame().w &&
                            mouseY >= button->getPos().y &&
                            mouseY <= button->getPos().y + button->getCurrentFrame().h)
                        {
                            sound_sys.playButtonSound();
                            button_action(window, uiManager, button, config, state);
                        }
                    }
                );
            }
            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP)
            {
                state.isDragging = false;
                state.TargetButton = nullptr;
            }
        }
*/


    }


}

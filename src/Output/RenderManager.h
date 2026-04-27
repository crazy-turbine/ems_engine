#pragma once

//#include "src/Common/function.h"
//#include "src/Gameplay/Create.h"
//#include "src/Common/json.h"
#include <vector>
#include <SDL3/SDL_ttf.h>
#include "src/Common/struct.h"
//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪

class ID_Converter;
class SceneManager;
class Entity;
class Render;

class RenderManager
{
public:

	static bool runRender(Render& window, SceneManager& uiManager);
	static void EntityRender(Entity& entity, Render& window);
	static void refreshUIText(std::string language, SceneManager& uiManager, SDL_Renderer* renderer, ID_Converter& converter);
private:
	static std::vector<Entity*> renderQueue;
};
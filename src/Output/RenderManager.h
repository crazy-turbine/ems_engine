#pragma once

//#include "src/Common/function.h"
//#include "src/Gameplay/Create.h"
//#include "src/Common/json.h"
#include <vector>
#include <SDL3/SDL_ttf.h>
#include "src/Common/struct.h"
//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪
namespace ems_engine
{

	class ID_Converter;
	class SceneManager;
	class ResourceManager;
	class TextureObject;
	class Render;

	class RenderManager
	{
	public:
		void setRecouceManagerPtr(ResourceManager* rc_manager);
		bool runRender(Render& window, SceneManager& uiManager);
		void refreshUIText(std::string language, SceneManager& uiManager, SDL_Renderer* renderer, ID_Converter& converter);
	private:
		void EntityRender(TextureObject& obj, Render& window, std::string sceneID);
		std::vector<TextureObject*> renderQueue;
		ResourceManager* resource_manager_ = nullptr;
	};
}

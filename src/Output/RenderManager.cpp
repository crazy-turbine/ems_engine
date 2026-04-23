#include "src/Core/RenderManager.h"
#include "src/Gameplay/ttf.h"
#include "third_party/magic_enum/magic_enum.hpp"
#include "src/Common/idConverter.h"
#include "src/Common/jsonManager.h"

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪

std::vector<Entity*> RenderManager::renderQueue;

void RenderManager::EntityRender(Entity& entity, Render& window)
{
	if (entity.getVisible())
	{
		window.RenderEntity(entity);
	}

}

bool RenderManager::runRender(Render& window, SceneManager& uiManager)
{
	window.beforeRender();
    renderQueue.clear();
	
	uiManager.getGlobalScene()->OneEntityMap
	(
		entity_type::back,
		[&](Entity* entity)
		{
			if (entity)
				EntityRender(*entity, window);
		}
	);
	uiManager.getCurrentScene()->eachEntity
	(
		[&] (Entity* entity)
		{
			renderQueue.push_back(entity);
		}
	);

	std::sort(renderQueue.begin(), renderQueue.end(), [](Entity* a, Entity* b) 
		{
			if (a->getLayer() != b->getLayer())
				return a->getLayer() < b->getLayer();
			else
			{
				return a->getPos().y + a->getCurrentFrame().h < b->getPos().y + b->getCurrentFrame().h;
			}
		});

	for (auto* e : renderQueue)
	{
		EntityRender(*e, window);
	}

	uiManager.getCurrentScene()->eachText
	(
		[&](ttf* text)
		{
			text->render(window);
		}
	);
	uiManager.getGlobalScene()->OneEntityMap
	(
		entity_type::object,
		[&](Entity* entity)
		{
			if (entity)
				EntityRender(*entity, window);
		}
	);

	window.display();
	return true;
}

void RenderManager::refreshUIText(const GameSetting& config, SceneManager& uiManager, SDL_Renderer* renderer, ID_Converter& converter)
{
	json text;
	std::string path = "text/";
	path += magic_enum::enum_name(config.Language);
	path += "/ui/";
	path += magic_enum::enum_name(uiManager.getSceneID());
	path += ".json";
	openJson(text, path);

	uiManager.getCurrentScene()->OneTextMap
	(
		text_type::default_static,
		[&](ttf* t, std::string key)
		{
			key = "/" + key;
			json::json_pointer key_ptr(key);
			std::string display_text;
			if (readJson(text, key_ptr, display_text))
			{
				t->setDisplayText(display_text);
				t->refreshTexture(renderer);
			}
		}
	);

	std::vector <std::string> json_path;


	uiManager.getCurrentScene()->OneTextMap
	(
		text_type::default_dynamic,
		[&](ttf* t, std::string key)
		{
			bool condition = true;
			std::string display_text = "";
			for (const auto& [path,ptr] : t->getConditionTarget())
			{
				std::cout << "[DEBUG]:test1 - refreshUIText jsonpath:"<< path << std::endl;
				std::cout << "[DEBUG]:test2 - refreshUIText jsonptr:"<< ptr << std::endl;
				if (JsonManager::addJson(path))
				{
					json_path.push_back(path);
				}
				json::json_pointer Tptr(ptr);
				readJson(JsonManager::getJson(path), Tptr, condition);
				if (!condition)
					break;
			}
			
			if (condition)
			{
				for (const auto& [Opath, Optr] : t->getHaveValueTextTarget())
				{
					std::string tmp_str;
					std::string return_str;
					std::string path;
					std::string ptr;
					converter.ConvertID(Opath, path);
					converter.ConvertID(Optr, ptr);
					if (JsonManager::addJson(path))
					{
						json_path.push_back(path);
					}
					json::json_pointer Tptr(ptr);
					readJson(JsonManager::getJson(path), Tptr, tmp_str);
					converter.ConvertID(tmp_str, return_str);
					display_text += return_str;
				}
			}
			else
			{
				for (const auto& [Opath, Optr] : t->getDefaultTextTarget())
				{
					std::string tmp_str;
					std::string return_str;
					std::string path;
					std::string ptr;
					converter.ConvertID(Opath, path);
					converter.ConvertID(Optr, ptr);
					if (JsonManager::addJson(path))
					{
						json_path.push_back(path);
					}
					json::json_pointer Tptr(ptr);
					readJson(JsonManager::getJson(path), Tptr, tmp_str);
					converter.ConvertID(tmp_str, return_str);
					display_text += tmp_str;
				}
			}
			std::cout << "[DEBUG]:test3 - refreshUIText display_text:" << display_text << std::endl;
			t->setDisplayText(display_text);
			t->refreshTexture(renderer);
		}
	);

}


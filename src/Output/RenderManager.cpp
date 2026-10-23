#include "RenderManager.h"
#include "src/Object/ttf.h"
//#include "third_party/magic_enum/magic_enum.hpp"
#include "src/Common/idConverter.h"
#include "src/Resource/jsonManager.h"
#include "include/ems_engine/Object/Object.h"
#include "include/ems_engine/Object/TextureObject.h"
#include "src/Output/Render.h"
#include "src/Scene/SceneManager.h"
#include "Scene/Scene.h"
#include "src/Resource/ResourceManager.h"

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪

namespace ems_engine
{



	void RenderManager::setRecouceManagerPtr(ResourceManager* rc_manager)
	{
		resource_manager_ = rc_manager;
	}

	void RenderManager::EntityRender(TextureObject& obj, Render& window, std::string sceneID)
	{
		if (resource_manager_ == nullptr)
		{
			std::cout << "[Error]:Resource Manager Pointer Not Found!" << std::endl;
			return;
		}
		if (obj.isVisible())
		{
			window.RenderEntity(obj.getRenderConfig(),resource_manager_->getTexture(obj.getRenderConfig().textureID,sceneID,window).get());
		}

	}

	bool RenderManager::runRender(Render& window,SceneManager& uiManager)
	{
		window.beforeRender();
		
		
		/*
		uiManager.getGlobalScene()->OneEntityMap
		(
			"back",
			[&](Entity* entity)
			{
				if (entity)
					EntityRender(*entity, window);
			}
		);*/
		if (uiManager.getCurrentScene()->getObjectMapDirtyFlag())
		{
			renderQueue.clear();
			uiManager.getCurrentScene()->ExecuteOneTypeObject<TextureObject>
			(
				[&](TextureObject* entity)
				{
					renderQueue.push_back(entity);
				}
			);
			std::sort(renderQueue.begin(), renderQueue.end(), [](TextureObject* a, TextureObject* b)
				{
					if (a->getLayer() != b->getLayer())
						return a->getLayer() < b->getLayer();
					else
					{
						return a->getPos().y + a->getSize().h < b->getPos().y + b->getSize().h;
					}
				});
			

		}
		else if(uiManager.getCurrentScene()->getObjectSortDirtyFlag())
		{
			std::stable_sort(renderQueue.begin(), renderQueue.end(), [](TextureObject* a, TextureObject* b)
				{
					if (a->getLayer() != b->getLayer())
						return a->getLayer() < b->getLayer();
					else
					{
						return a->getPos().y + a->getSize().h < b->getPos().y + b->getSize().h;
					}
				});
		}

		uiManager.getCurrentScene()->resetObjectMapDirtyFlag();
		uiManager.getCurrentScene()->resetObjectSortDirtyFlag();


		for (auto* e : renderQueue)
		{
			EntityRender(*e, window, uiManager.getSceneID());
		}

		uiManager.getCurrentScene()->eachText
		(
			[&](ttf* text)
			{
				text->render(window);
			}
		);
		uiManager.getGlobalScene()->ExecuteOneTypeObject<TextureObject>
		(
			[&](TextureObject* entity)
			{
				if (entity)
					EntityRender(*entity, window, "global");
			}
		);

		window.display();
		return true;
	}

	void RenderManager::refreshUIText(std::string language, SceneManager& uiManager, SDL_Renderer* renderer, ID_Converter& converter)
	{
		json text;
		std::string path = "text/";
		path += language;
		path += "/ui/";
		path += uiManager.getSceneID();
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
				for (const auto& [path, ptr] : t->getConditionTarget())
				{
					std::cout << "[DEBUG]:test1 - refreshUIText jsonpath:" << path << std::endl;
					std::cout << "[DEBUG]:test2 - refreshUIText jsonptr:" << ptr << std::endl;
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

}

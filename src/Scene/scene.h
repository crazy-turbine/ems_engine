#pragma once
#include<unordered_map>
#include"src/Common/enum.h"
#include <memory>
#include "src/Object/Entity.h"
#include "src/Object/ttf.h"
#include <functional>
namespace ems_engine
{

	class Scene
	{
	public:
		void addEntity(std::string type, std::string entityID, EntityConfig& configValue, Render& window);
		void addText(text_type type, std::string textID, TextConfig& configValue);
		void eachEntity(std::function<void(Entity*)> action);
		void eachEntity(std::function<void(Entity*, std::string key)> action);
		void OneEntityMap(std::string type, std::function<void(Entity*)> action);
		void OneEntityMap(std::string type, std::function<void(Entity*, std::string key)> action);
		Entity* getEntity(std::string type, std::string ID);
		void eachText(std::function<void(ttf*)> action);
		void eachText(std::function<void(ttf*, std::string key)> action);
		void OneTextMap(text_type type, std::function<void(ttf*)> action);
		void OneTextMap(text_type type, std::function<void(ttf*, std::string key)> action);
		ttf* getText(text_type type, std::string ID);
	private:
		std::unordered_map < text_type, std::unordered_map<std::string, std::unique_ptr<ttf>>> TextMap;

		std::unordered_map<std::string, std::unordered_map<std::string, std::unique_ptr<Entity>>> EntityMap;
	};
}

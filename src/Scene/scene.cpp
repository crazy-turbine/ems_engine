#include "scene.h"
#include <iostream>
namespace ems_engine
{

	void Scene::addEntity(std::string type, std::string entityID, EntityConfig& configValue, Render& window)
	{
		EntityMap[type].emplace
		(
			entityID, std::make_unique<Entity>(configValue, window)
		);
	}

	void Scene::addText(text_type type, std::string textID, TextConfig& configValue)
	{
		TextMap[type].emplace
		(
			textID, std::make_unique<ttf>(configValue)
		);
	}

	void Scene::eachEntity(std::function<void(Entity*)> action)
	{
		for (auto& [type, map] : EntityMap)
		{
			for (auto& [ID, entity] : map)
			{
				action(entity.get());
			}
		}
	}
	void Scene::eachEntity(std::function<void(Entity*, std::string key)> action)
	{
		for (auto& [type, map] : EntityMap)
		{
			for (auto& [ID, entity] : map)
			{
				action(entity.get(), ID);
			}
		}
	}
	void Scene::OneEntityMap(std::string type, std::function<void(Entity*)> action)
	{
		if (EntityMap.contains(type))
		{
			for (auto& [ID, entity] : EntityMap[type])
			{
				action(entity.get());
			}
		}
	}
	void Scene::OneEntityMap(std::string type, std::function<void(Entity*, std::string key)> action)
	{
		if (EntityMap.contains(type))
		{
			for (auto& [ID, entity] : EntityMap[type])
			{
				action(entity.get(), ID);
			}
		}
	}

	Entity* Scene::getEntity(std::string type, std::string ID)
	{
		if (EntityMap.contains(type))
		{
			if (EntityMap[type].contains(ID))
			{
				return EntityMap[type][ID].get();
			}
			std::cout << "[ERROR]:get Entity ID Not Found" << std::endl;
		}
		std::cout << "[ERROR]:Can't get Entity" << std::endl;
		return nullptr;
	}

	void Scene::eachText(std::function<void(ttf*)> action)
	{
		for (auto& [type, map] : TextMap)
		{
			for (auto& [ID, text] : map)
			{
				action(text.get());
			}
		}
	}
	void Scene::eachText(std::function<void(ttf*, std::string key)> action)
	{
		for (auto& [type, map] : TextMap)
		{
			for (auto& [ID, text] : map)
			{
				action(text.get(), ID);
			}
		}
	}
	void Scene::OneTextMap(text_type type, std::function<void(ttf*)> action)
	{
		if (TextMap.contains(type))
		{
			for (auto& [ID, text] : TextMap[type])
			{
				action(text.get());
			}
		}
	}
	void Scene::OneTextMap(text_type type, std::function<void(ttf*, std::string key)> action)
	{
		if (TextMap.contains(type))
		{
			for (auto& [ID, text] : TextMap[type])
			{
				action(text.get(), ID);
			}
		}
	}

	ttf* Scene::getText(text_type type, std::string ID)
	{
		if (TextMap.contains(type))
		{
			if (TextMap[type].contains(ID))
			{
				return TextMap[type][ID].get();
			}
			std::cout << "[ERROR]:get Text ID Not Found" << std::endl;
		}
		std::cout << "[ERROR]:Can't get Text" << std::endl;
		return nullptr;
	}
}

/*
void Scene::eachText(std::function<void(ttf*)> action)
{
	for (auto& [ID, text] : TextMap)
		action(text.get());
}
void Scene::eachText(std::function<void(ttf*, std::string key)> action)
{
	for (auto& [ID, text] : TextMap)
		action(text.get(), ID);
}*/
#include "sceneManager.h"
#include <iostream>
#include "Object/Create.h"
//#include "third_party/magic_enum/magic_enum.hpp"

namespace ems_engine
{
	SceneManager::SceneManager(ResourceManager* rcm, Render* render)
	{
		rc_mgr = rcm;
		render_sys = render;
	}
	Scene* SceneManager::getCurrentScene()
	{
		auto scene_IDIt = SceneMap.find(currentScene);
		if (scene_IDIt == SceneMap.end())
		{
			std::cout << "[ERROR]:Scene Not Create!(getCurrent)" << std::endl;
			return nullptr;
		}
		return SceneMap[currentScene].get();
	}
	Scene* SceneManager::getScene(std::string sceneID)
	{
		auto scene_IDIt = SceneMap.find(sceneID);
		if (scene_IDIt == SceneMap.end())
		{
			std::cout << "[ERROR]:Scene Not Create!(getSceneWithSceneID)" << std::endl;
			return nullptr;
		}
		return SceneMap[currentScene].get();
	}
	Scene* SceneManager::getGlobalScene()
	{
		auto scene_IDIt = SceneMap.find("global");
		if (scene_IDIt == SceneMap.end())
		{
			std::cout << "[ERROR]:Scene Not Create!(getGlobal)" << std::endl;
			return nullptr;
		}
		return SceneMap["global"].get();
	}
	std::string SceneManager::getSceneID()
	{
		return currentScene;
	}
	void SceneManager::setSceneID(std::string sceneID)
	{
		currentScene = sceneID;
		auto scene_IDIt = SceneMap.find(sceneID);
		if (scene_IDIt == SceneMap.end())
		{
			std::cout << "[Create]:Create Scene:" << sceneID << std::endl;
			SceneMap.emplace(currentScene, std::make_unique<Scene>());
		}
		createEntity(*this, *rc_mgr, *render_sys);
		createTEXT(*this, "zh_tw", rc_mgr);
	}
	void SceneManager::UpdateScene()
	{
		setSceneID(targetScene);
	}
	std::string SceneManager::getTargetSceneID()
	{
		return targetScene;
	}
	void SceneManager::setTargetSceneID(std::string sceneID)
	{
		targetScene = sceneID;
	}
	bool SceneManager::isSceneMatch()
	{
		if (currentScene == targetScene)
		{
			return true;
		}
		return false;
	}
	void SceneManager::clearScene()
	{
		auto scene_IDIt = SceneMap.find(currentScene);
		if (scene_IDIt == SceneMap.end())
		{
			std::cout << "[ERROR]:Scene Not Create!(clear)" << std::endl;
			return;
		}
		SceneMap.erase(currentScene);
	}
	void SceneManager::deleteAll()
	{
		SceneMap.clear();
	}
}

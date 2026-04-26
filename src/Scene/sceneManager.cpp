#include "sceneManager.h"
//#include "third_party/magic_enum/magic_enum.hpp"



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
Scene* SceneManager::getGlobalScene()
{
	auto scene_IDIt = SceneMap.find(scene_ID::global);
	if (scene_IDIt == SceneMap.end())
	{
		std::cout << "[ERROR]:Scene Not Create!(getGlobal)" << std::endl;
		return nullptr;
	}
	return SceneMap[scene_ID::global].get();
}
scene_ID SceneManager::getSceneID()
{
	return currentScene;
}
void SceneManager::setSceneID(scene_ID sceneID)
{
	currentScene = sceneID;
	auto scene_IDIt = SceneMap.find(sceneID);
	if (scene_IDIt == SceneMap.end())
	{
		std::cout << "[Create]:Create Scene:"<<magic_enum::enum_name(sceneID) << std::endl;
		SceneMap.emplace(currentScene, std::make_unique<Scene>());
	}
}
void SceneManager::UpdateScene()
{
	setSceneID(targetScene);
}
scene_ID SceneManager::getTargetSceneID()
{
	return targetScene;
}
void SceneManager::setTargetSceneID(scene_ID sceneID)
{
	targetScene = sceneID;
}
bool SceneManager::isSceneMatch()
{
	if (currentScene==targetScene)
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
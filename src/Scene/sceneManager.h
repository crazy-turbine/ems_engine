#pragma once
#include "scene.h"
#include<unordered_map>
#include "src/Common/enum.h"
#include <string>

namespace ems_engine
{
	class ResourceManager;
	class Render;

	class SceneManager
	{
	public:
		SceneManager(ResourceManager* rcm,Render* render);
		Scene* getCurrentScene();
		Scene* getGlobalScene();
		std::string getSceneID();
		void setSceneID(std::string sceneID);
		void UpdateScene();
		std::string getTargetSceneID();
		void setTargetSceneID(std::string sceneID);
		bool isSceneMatch();
		void clearScene();
		void deleteAll();
	private:
		std::unordered_map<std::string, std::unique_ptr<Scene>> SceneMap;
		std::string currentScene = "global";
		std::string targetScene = "global";
		ResourceManager* rc_mgr;
		Render* render_sys;
	};
}

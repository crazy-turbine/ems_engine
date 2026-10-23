#pragma once
#include <functional>
#include <string>
#include <memory>
#include <iostream>
#include "Object/Object.h"

namespace ems_engine
{
	class SceneManager;
	class SceneAPI
	{
	public:
		SceneAPI(SceneManager* scene_mgr);

		void setSceneID(std::string sceneID);
		void UpdateScene();
		std::string getTargetSceneID();
		void setTargetSceneID(std::string sceneID);

		void ExecuteSceneAllObject(std::string sceneID, std::function<void(Object*)> action);
		void ExecuteSceneAllObject(std::string sceneID, std::function<void(Object*, std::string key)> action);
		template<typename T = Object>
		void ExecuteSceneOneTypeObject(std::string sceneID, std::function<void(T*)> action)
		{
			SearchObjMap(sceneID,
			[&action](std::string ID, const std::unique_ptr<Object>& obj)
				{
					if (auto* casted = dynamic_cast<T*>(obj.get()))
					{
						action(casted);
					}
				}
			);
		}
		template<typename T = Object>
		void ExecuteSceneOneTypeObject(std::string sceneID, std::function<void(T*, std::string key)> action)
		{
			SearchObjMap(sceneID,
			[&action](std::string ID, const std::unique_ptr<Object>& obj)
				{
					if (auto* casted = dynamic_cast<T*>(obj.get()))
					{
						action(casted, ID);
					}
				}
			);
		}
		template<typename T = Object>
		void ExecuteSceneObject(std::string sceneID, std::string ID, std::function<void(T*)> action)
		{
			if (isObjExist(sceneID, ID))
			{
				if (auto* casted = dynamic_cast<T*>(getObj(sceneID, ID).get()))
				{
					action(casted);
				}
				else
					std::cout << "[ERROR]:Can't get Object - Wrong Type!" << std::endl;
			}
			else
				std::cout << "[ERROR]:get Object ID Not Found" << std::endl;
		}
	private:
		void SearchObjMap(std::string sceneID, std::function<void(std::string ID, const std::unique_ptr<Object>& obj)> find_obj_map);
		bool isObjExist(std::string sceneID ,std::string obj_id);
		const std::unique_ptr<Object>& getObj(std::string sceneID, std::string ID);
		SceneManager* scene_mgr_;
	};
}
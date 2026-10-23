#include "include/ems_engine/SceneAPI.h"
#include "Scene/sceneManager.h";

namespace ems_engine
{
	SceneAPI::SceneAPI(SceneManager* scene_mgr)
	{
		scene_mgr_ = scene_mgr;
	}

	void SceneAPI::setSceneID(std::string sceneID)
	{
		scene_mgr_->setSceneID(sceneID);
	}
	void SceneAPI::UpdateScene()
	{
		scene_mgr_->UpdateScene();
	}
	std::string SceneAPI::getTargetSceneID()
	{
		return scene_mgr_->getTargetSceneID();
	}
	void SceneAPI::setTargetSceneID(std::string sceneID)
	{
		scene_mgr_->setTargetSceneID(sceneID);
	}

	void SceneAPI::ExecuteSceneAllObject(std::string sceneID, std::function<void(Object*)> action)
	{
		auto* scene_ = scene_mgr_->getScene(sceneID);
		if (scene_ == nullptr)
			return;
		scene_->ExecuteAllObject(action);
	}
	void SceneAPI::ExecuteSceneAllObject(std::string sceneID, std::function<void(Object*, std::string key)> action)
	{
		auto* scene_ = scene_mgr_->getScene(sceneID);
		if (scene_ == nullptr)
			return;
		scene_->ExecuteAllObject(action);
	}


	void SceneAPI::SearchObjMap(std::string sceneID, std::function<void(std::string ID, const std::unique_ptr<Object>& obj)> find_obj_map)
	{
		auto* scene_ = scene_mgr_->getScene(sceneID);
		if (scene_ == nullptr)
			return;
		for (const auto& [ID, obj] : scene_->getObjectMap())
		{
			find_obj_map(ID, obj);
		}

	}
	bool SceneAPI::isObjExist(std::string sceneID, std::string obj_id)
	{
		auto* scene_ = scene_mgr_->getScene(sceneID);
		if (scene_ == nullptr)
			return false;
		if (scene_->getObjectMap().contains(obj_id))
		{
			return true;
		}
		else
			return false;
	}
	const std::unique_ptr<Object>& SceneAPI::getObj(std::string sceneID, std::string ID)
	{
		auto* scene_ = scene_mgr_->getScene(sceneID);
		const auto& obj_map = scene_->getObjectMap();
		return obj_map.at(ID);
	}
}
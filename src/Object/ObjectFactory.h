#pragma once
#include <functional>
#include <string>
#include <unordered_set>
#include "src/Resource/JsonFileIO.h"

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110
//上面這段保佑這個專案乖乖，勿刪


namespace ems_engine
{
	class Sprite;
	class ttf;
	class SceneManager;
	class Scene;
	class ResourceManager;
	class Render;


	class Object;
	class TextureObject;

	//UI
	class UIElement;
	class UIStateElement;
	class UIButton;
	class UICheckBox;
	class UISlider;

	using string_set = std::unordered_set<std::string>;

	class ObjectFactory
	{
	public:
		ObjectFactory(ResourceManager* rc_mgr, Render* render_sys, std::string base_path);
		void createSceneObject(Scene* scene,std::string sceneID);
	private:
		template <typename T>
		bool assignJsonValue(T& value, std::string key, const json* const obj_data, string_set& assigned_keys)
		{
			json::json_pointer js_ptr(key);
			if (assigned_keys.count(key) == 0)
			{
				if (readJson(*obj_data, js_ptr, value))
				{
					assigned_keys.insert(key);
					return true;
				}
			}
			return false;
		}

		void setObject(Object* obj, const json* const obj_data, string_set& assigned_keys);
		void setTextureObject(TextureObject* obj, const json* const obj_data, string_set& assigned_keys, std::string scene_id);
		//UI
		void setUIElement(UIElement* obj,const json* const obj_data, string_set& assigned_keys, std::string scene_id);
		void setUIStateElement(UIStateElement* obj, const json* const obj_data, string_set& assigned_keys, std::string scene_id);
		void setUIButton(UIButton* obj, const json* const obj_data, string_set& assigned_keys, std::string scene_id);
		void setUICheckBox(UICheckBox* obj, const json* const obj_data, string_set& assigned_keys, std::string scene_id);
		void setUISlider(UISlider* obj, const json* const obj_data, string_set& assigned_keys, std::string scene_id);

		ResourceManager* rc_mgr_;
		Render* render_sys_;
		std::string base_path_ = "";
	};


	void createEntity(SceneManager& Manager, ResourceManager& rc_mgr, Render& window);
	void createTEXT(SceneManager& Manager, std::string lang, ResourceManager* rc_mgr);
	//void createSprite(Render& window, int w, int h);
	void createMap(Render& window, int w, int h);
	//Sprite* getSprite(const std::string& name);
	//Map* getMap(const std::string& name);
}

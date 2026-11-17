#include "ObjectFactory.h"

#include <vector>
#include <filesystem>

//#include "src/Object/Entity.h"

#define MAGIC_ENUM_RANGE_MAX 2000
#include "src/Scene/sceneManager.h"
#include "third_party/magic_enum/magic_enum.hpp"
#include "Common/toHash.h"
#include "include/ems_engine/Object/UIElement/UIButton.h"
#include "include/ems_engine/Object/UIElement/UICheckBox.h"
#include "include/ems_engine/Object/UIElement/UIElement.h"
#include "include/ems_engine/Object/UIElement/UISlider.h"
#include "include/ems_engine/Object/UIElement/UIStateElement.h"
#include "Resource/ResourceManager.h"
#include "Scene/Scene.h"

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110


namespace ems_engine
{

	//std::map<std::string, Sprite*> SpriteMap;

	ObjectFactory::ObjectFactory(ResourceManager* rc_mgr, Render* render_sys, std::string base_path)
		:rc_mgr_(rc_mgr),render_sys_(render_sys),base_path_(base_path)
	{
		if (rc_mgr == nullptr)
			throw std::invalid_argument("ResourceManager is nullptr!");
		if (render_sys == nullptr)
			throw std::invalid_argument("Render is nullptr!");
	}

	void ObjectFactory::createSceneObject(Scene* scene, std::string sceneID)
	{
		json scene_data;
		std::string filename = sceneID + ".json";
		std::filesystem::path path = base_path_;
		path = path / "scene" / filename;
		openJson(scene_data, path.string());
		const json& objs_data = scene_data.at("/objects"_json_pointer);
		for (const auto& [id,data] : objs_data.items())
		{
			std::string extends = "null";
			std::string obj_type = "null";
			readJson(data, "/type"_json_pointer, obj_type);
			std::vector<const json*> obj_data_list;
			std::unordered_set<std::string> extends_list;
			extends_list.insert(id);
			const json* target_data = &data;
			obj_data_list.push_back(target_data);
			
			while (obj_type == "null")
			{
				extends = "null";
				readJson(*target_data, "/extends"_json_pointer, extends);
				if (extends != "null")
				{
					if (extends_list.count(extends))
					{
						std::cout << "[ERROR]: Circular object inheritance detected!" << std::endl;
						std::cout << "[ERROR-INFO]: ext/obj_id/scene:" << extends << "/" << id << "/" << sceneID << std::endl;
						break;
					}
					extends_list.insert(extends);
					if (objs_data.contains(extends))
					{
						target_data = &objs_data.at(extends);
						obj_data_list.push_back(target_data);
						readJson(*target_data, "/type"_json_pointer, obj_type);
					}
					else
					{
						std::cout << "[ERROR]: Extends not found!" << std::endl;
						std::cout << "[ERROR-INFO]: ext/obj_id/scene:" << extends << "/" << id << "/" << sceneID << std::endl;
						break;
					}
				}
				else
				{
					std::cout << "[ERROR]: Object type undefined!" << std::endl;
					std::cout << "[ERROR-INFO]: obj_id/scene:" << id << "/" << sceneID << std::endl;
					break;
				}
			}

			if (obj_type == "null")
			{
				continue;
			}

			std::unordered_set<std::string> assigned_keys;

			//UI
			if (obj_type == "UIElement")
			{
				auto obj = scene->addObject<UIElement>(id);
				for (const auto obj_data : obj_data_list)
				{
					setUIElement(obj, obj_data, assigned_keys);
				}
				continue;
			}
			if (obj_type == "UIStateElement")
			{
				auto obj = scene->addObject<UIStateElement>(id);
				for (const auto obj_data : obj_data_list)
				{
					setUIStateElement(obj, obj_data, assigned_keys);
				}
				continue;
			}
			if (obj_type == "UIButton")
			{
				auto obj = scene->addObject<UIButton>(id);
				for (const auto obj_data : obj_data_list)
				{
					setUIButton(obj, obj_data, assigned_keys);
				}
				continue;
			}
			if (obj_type == "UICheckBox")
			{
				auto obj = scene->addObject<UICheckBox>(id);
				for (const auto obj_data : obj_data_list)
				{
					setUICheckBox(obj, obj_data, assigned_keys);
				}
				continue;
			}
			if (obj_type == "UISlider")
			{
				auto obj = scene->addObject<UISlider>(id);
				for (const auto obj_data : obj_data_list)
				{
					setUISlider(obj, obj_data, assigned_keys);
				}
				continue;
			}
			std::cout << "[ERROR]: Object type not found!" << std::endl;
		}
	}

	void ObjectFactory::setObject(Object* obj, const json* const obj_data, std::unordered_set<std::string>& assigned_keys)
	{
		float x=0, y=0, w=0, h=0;
		if(assigned_keys.count("x") == 0)
		{
			readJson(*obj_data, "/x"_json_pointer, x);
			obj->setPosX(x);
			assigned_keys.insert("x");
		}
		if (assigned_keys.count("y") == 0)
		{
			readJson(*obj_data, "/y"_json_pointer, y);
			obj->setPosY(y);
			assigned_keys.insert("y");
		}
		if (assigned_keys.count("w") == 0)
		{
			readJson(*obj_data, "/w"_json_pointer, w);
			obj->setSizeW(w);
			assigned_keys.insert("w");
		}
		if (assigned_keys.count("h") == 0)
		{
			readJson(*obj_data, "/h"_json_pointer, h);
			obj->setSizeH(h);
			assigned_keys.insert("h");
		}
	}
	void ObjectFactory::setTextureObject(TextureObject* obj, const json* const obj_data, std::unordered_set<std::string>& assigned_keys)
	{

	}
	//UI
	void ObjectFactory::setUIElement(UIElement* obj, const json* const obj_data, std::unordered_set<std::string>& assigned_keys)
	{

	}
	void ObjectFactory::setUIStateElement(UIStateElement* obj, const json* const obj_data, std::unordered_set<std::string>& assigned_keys)
	{

	}
	void ObjectFactory::setUIButton(UIButton* obj, const json* const obj_data, std::unordered_set<std::string>& assigned_keys)
	{

	}
	void ObjectFactory::setUICheckBox(UICheckBox* obj, const json* const obj_data, std::unordered_set<std::string>& assigned_keys)
	{

	}
	void ObjectFactory::setUISlider(UISlider* obj, const json* const obj_data, std::unordered_set<std::string>& assigned_keys)
	{

	}




	void createEntity(SceneManager& Manager, ResourceManager& rc_mgr, Render& window)
	{
		json config;
		std::string
			path = "res/Entity_config/";
		path += Manager.getSceneID();
		path += ".json";
		openJson(config, path);
		for (const auto& item : config)
		{
			EntityConfig configValue;
			std::string entityID;
			std::string EntityType;
			std::string to_enum;
			std::string to_vector = "";
			configValue.sceneID = Manager.getSceneID();
			readJson(item, "/x"_json_pointer, configValue.x);
			readJson(item, "/y"_json_pointer, configValue.y);
			readJson(item, "/w"_json_pointer, configValue.w);
			readJson(item, "/h"_json_pointer, configValue.h);
			readJson(item, "/series_num"_json_pointer, configValue.series_num);
			readJson(item, "/path1"_json_pointer, to_vector);
			if(!to_vector.empty())
			configValue.TexturePath.push_back(to_vector);
			to_vector = "";
			readJson(item, "/entity_type"_json_pointer, EntityType);
			readJson(item, "/path2"_json_pointer, to_vector);
			if (!to_vector.empty())
				configValue.TexturePath.push_back(to_vector);
			to_vector = "";
			readJson(item, "/actionID"_json_pointer, configValue.actionID);
			readJson(item, "/path3"_json_pointer, to_vector);
			if (!to_vector.empty())
				configValue.TexturePath.push_back(to_vector);
			to_vector = "";
			readJson(item, "/path4"_json_pointer, to_vector);
			if (!to_vector.empty())
				configValue.TexturePath.push_back(to_vector);
			to_vector = "";
			readJson(item, "/slide_button"_json_pointer, configValue.slide_button);
			readJson(item, "/layer"_json_pointer, to_enum);
			if (magic_enum::enum_cast<layer_ID>(to_enum).has_value())
				configValue.layer = static_cast<int>(magic_enum::enum_cast<layer_ID>(to_enum).value());
			else
			{
				std::cout << "[ERROR]:LayerID undefined - " << to_enum << std::endl;
				continue;
			}			
			readJson(item, "/entityID"_json_pointer, entityID);
			std::cout << "[DEBUG]:Create Entity - " << entityID << std::endl;

			for (const auto& texture_path : configValue.TexturePath)
			{
				rc_mgr.loadTexture(texture_path, Manager.getSceneID(), window);
			}

			if (EntityType == "UIElement")
			{
				UIElement* obj = Manager.getCurrentScene()->addObject<UIElement>(entityID);
				obj->setPos(configValue.x, configValue.y);
				obj->setSize(configValue.w, configValue.h);
				if (0 < configValue.TexturePath.size())
					obj->setCurrentTextureID(string_toHash(configValue.TexturePath.at(0)));
				obj->setLayer(configValue.layer);
				continue;
			}
			if (EntityType == "UIStateElement")
			{
				UIStateElement* obj = Manager.getCurrentScene()->addObject<UIStateElement>(entityID);
				obj->setPos(configValue.x, configValue.y);
				obj->setSize(configValue.w, configValue.h);
				if (0 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(0)}, "Default");
				if (1 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(1)}, "Hover");
				if (2 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(2)}, "CheckON");
				if (3 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(3)}, "Hover_CheckON");
				obj->setLayer(configValue.layer);
				continue;
			}
			if (EntityType == "UIButton")
			{
				UIButton* obj = Manager.getCurrentScene()->addObject<UIButton>(entityID);
				obj->setPos(configValue.x, configValue.y);
				obj->setSize(configValue.w, configValue.h);
				if (0 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(0)}, "Default");
				if (1 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(1)}, "Hover");
				if (2 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(2)}, "CheckON");
				if (3 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(3)}, "Hover_CheckON");
				obj->setLayer(configValue.layer);
				obj->setDefaultState("Default");
				obj->setHoverState("Hover");
				continue;
			}
			if (EntityType == "UICheckBox")
			{
				UICheckBox* obj = Manager.getCurrentScene()->addObject<UICheckBox>(entityID);
				obj->setPos(configValue.x, configValue.y);
				obj->setSize(configValue.w, configValue.h);
				if (0 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(0)}, "Default");
				if (1 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(1)}, "Hover");
				if (2 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(2)}, "CheckON");
				if (3 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(3)}, "Hover_CheckON");
				obj->setLayer(configValue.layer);
				obj->setDefaultState("Default");
				obj->setHoverState("Hover");
				obj->setDefaultState("CheckON");
				obj->setHoverState("Hover_CheckON");
				continue;
			}
			if (EntityType == "UISlider")
			{
				UISlider* obj = Manager.getCurrentScene()->addObject<UISlider>(entityID);
				obj->setPos(configValue.x, configValue.y);
				obj->setSize(configValue.w, configValue.h);
				if (0 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(0)}, "Default");
				if (1 < configValue.TexturePath.size())
					obj->setVisualGroup(std::vector<std::string>{configValue.TexturePath.at(1)}, "Hover");
				if (2 < configValue.TexturePath.size())
					obj->setCurrentTextureID(string_toHash(configValue.TexturePath.at(2)), 1);
				obj->setLayer(configValue.layer);
				obj->setDefaultState("Default");
				obj->setHoverState("Hover");
				obj->setDefaultState("CheckON");
				obj->setHoverState("Hover_CheckON");
				continue;
			}
			std::cout << "[Error]:Entity Type Not Found!" << std::endl;
			//Manager.getCurrentScene()->addObject<>(EntityType, entityID, configValue, window);
		}
	}

	void createTEXT(SceneManager& Manager, std::string lang, ResourceManager* rc_mgr)
	{
		json style;
		std::string path = "res/Text_config/style.json";
		openJson(style, path);

		json config;
		path = "res/Text_config/";
		path += Manager.getSceneID();
		path += ".json";
		openJson(config, path);


		json::json_pointer Fptr("/font");
		Fptr.push_back(lang);

		for (const auto& item : config)
		{
			TextConfig configValue;
			std::string textID;
			std::string to_enum;
			std::string fontID;
			std::string colorID;
			int r = 255, g = 255, b = 255, a = 255;
			readJson(item, "/size"_json_pointer, configValue.size);
			readJson(item, "/startX"_json_pointer, configValue.startX);
			readJson(item, "/endX"_json_pointer, configValue.endX);
			readJson(item, "/y"_json_pointer, configValue.y);
			readJson(item, "/font"_json_pointer, fontID);
			Fptr.push_back(fontID);
			readJson(style, Fptr, configValue.path);
			Fptr.pop_back();
			readJson(item, "/color"_json_pointer, colorID);
			json::json_pointer Cptr("/color");
			std::cout << "[DEBUG]: colorID:" << colorID << std::endl;
			Cptr.push_back(colorID);
			Cptr.push_back("r");
			readJson(style, Cptr, r);
			Cptr.pop_back();
			Cptr.push_back("g");
			readJson(style, Cptr, g);
			Cptr.pop_back();
			Cptr.push_back("b");
			readJson(style, Cptr, b);
			Cptr.pop_back();
			Cptr.push_back("a");
			readJson(style, Cptr, a);
			configValue.color = { (Uint8)r,(Uint8)g,(Uint8)b,(Uint8)a };
			readJson(item, "/textID"_json_pointer, textID);
			readJson(item, "/line_type"_json_pointer, to_enum);
			if (magic_enum::enum_cast<line_type>(to_enum).has_value())
				configValue.Ltype = magic_enum::enum_cast<line_type>(to_enum).value();
			else
			{
				std::cout << "[ERROR]:line_type undefined" << std::endl << to_enum << std::endl;
				continue;
			}
			readJson(item, "/text_type"_json_pointer, to_enum);
			if (magic_enum::enum_cast<text_type>(to_enum).has_value())
				configValue.Ttype = magic_enum::enum_cast<text_type>(to_enum).value();
			else
			{
				std::cout << "[ERROR]:text_type undefined" << std::endl << to_enum << std::endl;
				continue;
			}
			if (configValue.Ttype == text_type::default_dynamic)
			{
				for (const auto& ar : item["conditionTarget"])
				{
					std::string to_vec_path, to_vec_ptr;
					readJson(ar, "/jsonPath"_json_pointer, to_vec_path);
					readJson(ar, "/jsptr"_json_pointer, to_vec_ptr);
					configValue.conditionTarget.push_back({ to_vec_path, to_vec_ptr });
				}
				for (const auto& ar : item["default_text"])
				{
					std::string to_vec_path, to_vec_ptr;
					readJson(ar, "/jsonPath"_json_pointer, to_vec_path);
					readJson(ar, "/jsptr"_json_pointer, to_vec_ptr);
					configValue.default_text.push_back({ to_vec_path, to_vec_ptr });
				}
				for (const auto& ar : item["haveValue_text"])
				{
					std::string to_vec_path, to_vec_ptr;
					readJson(ar, "/jsonPath"_json_pointer, to_vec_path);
					readJson(ar, "/jsptr"_json_pointer, to_vec_ptr);
					configValue.haveValue_text.push_back({ to_vec_path, to_vec_ptr });
				}
			}

			Manager.getCurrentScene()->addText(configValue.Ttype, textID, configValue, rc_mgr);
		}
	}
	void createSprite(Render& window, int w, int h)
	{

	}

	void createMap(Render& window, int w, int h)
	{

	}
	/*
	Sprite* getSprite(const std::string& name)
	{
		auto it = SpriteMap.find(name);
		if (it != SpriteMap.end())
			return it->second;
		std::cout << "getSprite	Error:Sprite Not Found" << std::endl;
		return nullptr;
	}*/
}

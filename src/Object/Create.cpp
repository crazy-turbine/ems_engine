#include "src/Object/Create.h"
#include "src/Object/Entity.h"
#include "src/Resource/json.h"
#include "third_party/magic_enum/magic_enum.hpp"

//111110110100000 1000001001110010 100111001010110 100111001010110 1001100100000101 100111001111110


namespace ems_engine
{

	std::map<std::string, Sprite*> SpriteMap;

	void createEntity(Render& window, SceneManager& Manager)
	{
		json config;
		std::string path = "res/Entity_config/";
		path += Manager.getSceneID();
		path += ".json";
		openJson(config, path);
		for (const auto& item : config)
		{
			EntityConfig configValue;
			std::string entityID;
			std::string EntityType;
			std::string to_enum;
			configValue.sceneID = Manager.getSceneID();
			readJson(item, "/x"_json_pointer, configValue.x);
			readJson(item, "/y"_json_pointer, configValue.y);
			readJson(item, "/w"_json_pointer, configValue.w);
			readJson(item, "/h"_json_pointer, configValue.h);
			readJson(item, "/series_num"_json_pointer, configValue.series_num);
			readJson(item, "/path1"_json_pointer, configValue.TexturePath.at(0));
			readJson(item, "/entity_type"_json_pointer, EntityType);
			readJson(item, "/path2"_json_pointer, configValue.TexturePath.at(1));
			readJson(item, "/actionID"_json_pointer, configValue.actionID);
			readJson(item, "/path3"_json_pointer, configValue.TexturePath.at(2));
			readJson(item, "/path4"_json_pointer, configValue.TexturePath.at(3));
			readJson(item, "/slide_button"_json_pointer, configValue.slide_button);
			readJson(item, "/layer"_json_pointer, to_enum);
			if (magic_enum::enum_cast<layer_ID>(to_enum).has_value())
				configValue.layer = static_cast<int>(magic_enum::enum_cast<layer_ID>(to_enum).value());
			else
			{
				std::cout << "[ERROR]:LayerID undefined" << std::endl << to_enum << std::endl;
				continue;
			}

			readJson(item, "/entityID"_json_pointer, entityID);



			Manager.getCurrentScene()->addEntity(EntityType, entityID, configValue, window);
		}
	}

	void createTEXT(SceneManager& Manager, std::string lang)
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

			Manager.getCurrentScene()->addText(configValue.Ttype, textID, configValue);
		}
	}
	void createSprite(Render& window, int w, int h)
	{

	}

	void createMap(Render& window, int w, int h)
	{

	}

	Sprite* getSprite(const std::string& name)
	{
		auto it = SpriteMap.find(name);
		if (it != SpriteMap.end())
			return it->second;
		std::cout << "getSprite	Error:Sprite Not Found" << std::endl;
		return nullptr;
	}
}

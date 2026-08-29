#pragma once
#include<unordered_map>
#include"src/Common/enum.h"
#include <memory>
#include "src/Object/ttf.h"
#include <functional>
#include <iostream>
#include <type_traits>
#include "src/Object/Object.h"
#include "src/Object/TextureObject.h"
namespace ems_engine
{
	class Object;
	class Scene
	{
	public:
		template<typename T>
		T* addObject(std::string objectID)
		{
			auto ptr = std::make_unique<T>();
			auto raw_ptr = ptr.get();
			if (ObjectMap.try_emplace(objectID, std::move(ptr)).second)
			{
				if constexpr (std::is_base_of_v<TextureObject, T>)
				{
					raw_ptr->setOnTransformChangedCallback
					([this]()
						{
							this->onObjectTransformChanged();
						}
					);
				}
				obj_map_dirty_flag = true;
				return raw_ptr;
			}
			else
			{
				std::cout << "[Error]: Object already exists"<<std::endl;
				return nullptr;
			}
		}
		void addText(text_type type, std::string textID, TextConfig& configValue, ResourceManager* rc_mgr);
		void ExecuteAllObject(std::function<void(Object*)> action);
		void ExecuteAllObject(std::function<void(Object*, std::string key)> action);
		template<typename T = Object>
		void ExecuteOneTypeObject(std::function<void(T*)> action)
		{
			for (auto& [ID, obj] : ObjectMap)
			{
				if (auto* casted = dynamic_cast<T*>(obj.get()))
				{
					action(casted);
				}
			}
		}
		template<typename T = Object>
		void ExecuteOneTypeObject(std::function<void(T*, std::string key)> action)
		{
			for (auto& [ID, obj] : ObjectMap)
			{
				if (auto* casted = dynamic_cast<T*>(obj.get()))
				{
					action(casted, ID);
				}
			}
		}
		template<typename T = Object>
		T* getObject(std::string ID)
		{
			if (ObjectMap.contains(ID))
			{
				if (auto* casted = dynamic_cast<T*>(ObjectMap[ID].get()))
				{
					return casted;
				}
				else
					std::cout << "[ERROR]:Can't get Object - Wrong Type!" << std::endl;
			}
			else
				std::cout << "[ERROR]:get Object ID Not Found" << std::endl;
			
			return nullptr;
			
		}
		void eachText(std::function<void(ttf*)> action);
		void eachText(std::function<void(ttf*, std::string key)> action);
		void OneTextMap(text_type type, std::function<void(ttf*)> action);
		void OneTextMap(text_type type, std::function<void(ttf*, std::string key)> action);
		ttf* getText(text_type type, std::string ID);

		bool getObjectMapDirtyFlag();
		void resetObjectMapDirtyFlag();

		void onObjectTransformChanged();
		bool getObjectSortDirtyFlag();
		void resetObjectSortDirtyFlag();

	private:
		bool obj_map_dirty_flag = false;
		bool obj_sort_dirty_flag = false;
		

		std::unordered_map < text_type, std::unordered_map<std::string, std::unique_ptr<ttf>>> TextMap;

		//std::unordered_map<std::string, >> EntityMap;
		std::unordered_map < std::string, std::unique_ptr<Object>> ObjectMap;
	};
}

#pragma once
#include<unordered_map>
#include"src/Common/enum.h"
#include <memory>
#include "src/Object/ttf.h"
#include <functional>
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
			if (EntityMap.try_emplace(objectID, ptr).second)
			{
				auto raw_ptr = ptr.get();
				return raw_ptr;
			}
			else
			{
				std::cout<<"[Error]: Object already exists"
				return nullptr;
			}
		}
		void addText(text_type type, std::string textID, TextConfig& configValue);
		void getAllObject(std::function<void(Object*)> action);
		void getAllObject(std::function<void(Object*, std::string key)> action);
		/*template<typename T>
		void getOneTypeObject(std::function<void(Object*)> action);
		template<typename T>
		void getOneTypeObject(std::function<void(Object*, std::string key)> action);
		*/
		Object* getObject(std::string type, std::string ID);
		void eachText(std::function<void(ttf*)> action);
		void eachText(std::function<void(ttf*, std::string key)> action);
		void OneTextMap(text_type type, std::function<void(ttf*)> action);
		void OneTextMap(text_type type, std::function<void(ttf*, std::string key)> action);
		ttf* getText(text_type type, std::string ID);
	private:
		std::unordered_map < text_type, std::unordered_map<std::string, std::unique_ptr<ttf>>> TextMap;

		//std::unordered_map<std::string, >> EntityMap;
		std::unordered_map < std::string, std::unique_ptr<Object>> EntityMap;
	};
}

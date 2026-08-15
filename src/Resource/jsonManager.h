#pragma once
#include <unordered_map>
#include "json.h"
namespace ems_engine
{

	class JsonManager
	{
	public:
		static bool addJson(std::string path);
		static json& getJson(std::string path);
		static void delJson(std::string path);
	private:
		static std::unordered_map<std::string, json> JsonMap;
	};
}

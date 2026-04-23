#include "src/Resource/jsonManager.h"

std::unordered_map<std::string, json> JsonManager::JsonMap;

bool JsonManager::addJson(std::string path)
{
	if (JsonMap.contains(path))
	{
		return false;
	}
	json data;
	openJson(data, path);
	JsonMap.emplace(path, data);
	return true;
}

json& JsonManager::getJson(std::string path)
{
	if (!JsonMap.contains(path))
	{
		throw std::runtime_error("[ERROR]:Json not create!");
	}
	return JsonMap.at(path);
}

void JsonManager::delJson(std::string path)
{
	if (JsonMap.erase(path) == 0)
	{
		std::cout << "[DEBUG]:Json not create!" << std::endl;
	}
	
}
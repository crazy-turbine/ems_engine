#include "Action.h"
#include "src/Resource/jsonManager.h"
#include "src/Output/RenderManager.h"

void delSlot(int series)
{
	json default_slot;
	JsonManager::addJson("saves/save_list.json");
	json& savelist = JsonManager::getJson("saves/save_list.json");
	std::string s_ptr = "/slot/" + std::to_string(series - 1);
	json::json_pointer ptr(s_ptr);
	readJson(savelist, "/Default"_json_pointer, default_slot);
	writeJson(savelist, ptr, default_slot);
	saveJson(savelist, "saves/save_list.json");
}
void coverSlot(int series)
{
	delSlot(series);
	json& savelist = JsonManager::getJson("saves/save_list.json");
	std::string s_ptr = "/slot/" + std::to_string(series - 1);
	json::json_pointer ptr(s_ptr + "/isCreated");
	bool isCreated = true;
	writeJson(savelist, ptr, isCreated);
}
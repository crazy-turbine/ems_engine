#include "src/Common/idConverter.h"
#include "src/Resource/json.h"
#include "src/Resource/jsonManager.h"
//#include "third_party/magic_enum/magic_enum.hpp"
#include <string>

ID_Converter::ID_Converter()
{
	json ConvertConfig;
	openJson(ConvertConfig, "res/setting/convert_config.json");
	std::string id, path, ptr;
	for (const auto& item : ConvertConfig)
	{

		readJson(item, "/id"_json_pointer, id);
		readJson(item, "/path"_json_pointer, path);
		readJson(item, "/ptr"_json_pointer, ptr);
		JsonTarget tmp_tar{ path ,ptr };
		JsonConvertMap.emplace(id, tmp_tar);
	}

}
void ID_Converter::ConvertID(const std::string& str, std::string& returnVal)
{
	returnVal.clear();
	std::string id;
	size_t lastpos = 0;
	size_t pos = 0;
	bool convert = true;
	while (convert)
	{
		pos = str.find("{", pos);
		size_t end_pos = str.find("}", pos);
		if (pos == std::string::npos || end_pos == std::string::npos)
		{
			convert = false;
			break;
		}
		returnVal.append(str, lastpos, pos - lastpos);
		id = str.substr(pos + 1, end_pos - pos - 1);
		auto VIt = VaribleConvertMap.find(id);
		if (VIt != VaribleConvertMap.end())
		{
			std::string convertValue = VIt->second();
			returnVal.append(convertValue);
			pos = end_pos + 1;
			lastpos = pos;
			continue;
		}
		auto JIt = JsonConvertMap.find(id);
		if (JIt != JsonConvertMap.end())
		{
			std::string convertValue;
			JsonManager::addJson(JIt->second.jsonPath);
			json::json_pointer ptr(JIt->second.jsptr);
			readJson(JsonManager::getJson(JIt->second.jsonPath), ptr, convertValue);
			returnVal.append(convertValue);
			pos = end_pos +1;
			lastpos = pos;
			continue;
		}
		returnVal.append("[ERROR]");
		throw std::runtime_error("[ERROR]:Convert Faild! - ID Not Found" + id);
	}
	returnVal.append(str.substr(lastpos));
}


#pragma once
#include <unordered_map>
#include <functional>
#include <string>
#include "src/Common/struct.h"

namespace ems_engine
{
	struct JsonTarget;

	class ID_Converter
	{
	public:
		using Getter = std::function<std::string()>;
		ID_Converter();
		virtual ~ID_Converter() {};
		virtual void CustomConverter() = 0;
		void ConvertID(const std::string& str, std::string& returnVal);
	protected:
		std::unordered_map<std::string, Getter> VaribleConvertMap;
		std::unordered_map<std::string, JsonTarget> JsonConvertMap;
	};
}

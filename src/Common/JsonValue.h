#pragma once
#include<variant>
#include<string>
#include<functional>

namespace ems_engine
{

	using jsVal = std::variant<int, bool, double, std::string, std::nullptr_t>;

	class JsonValue
	{
	public:
		JsonValue();
		JsonValue(int v);
		JsonValue(bool v);
		JsonValue(double v);
		JsonValue(const std::string& v);
		JsonValue(const char* v);
		JsonValue(std::nullptr_t v);

		JsonValue& operator=(int v);
		JsonValue& operator=(bool v);
		JsonValue& operator=(double v);
		JsonValue& operator=(const std::string& v);
		JsonValue& operator=(const char* v);
		JsonValue& operator=(std::nullptr_t v);

		bool isInt();
		bool isBool();
		bool isDouble();
		bool isString();
		bool isNULL();

		template<typename T>
		const T& get();
		void get(auto&& callback);

	private:
		jsVal val;
	};
}

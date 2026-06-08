#include "JsonValue.h"

JsonValue::JsonValue() :val(nullptr){}
JsonValue::JsonValue(int v) :val(v) {}
JsonValue::JsonValue(bool v) :val(v) {}
JsonValue::JsonValue(double v) :val(v) {}
JsonValue::JsonValue(const std::string& v) :val(v) {}
JsonValue::JsonValue(const char* v) :val(std::string(v)) {}
JsonValue::JsonValue(std::nullptr_t v) :val(v) {}

JsonValue& JsonValue::operator=(int v) { val = v; return *this; }
JsonValue& JsonValue::operator=(bool v) { val = v; return *this;}
JsonValue& JsonValue::operator=(double v) { val = v; return *this; }
JsonValue& JsonValue::operator=(const std::string& v) { val = v; return *this; }
JsonValue& JsonValue::operator=(const char* v) { val = v; return *this; }
JsonValue& JsonValue::operator=(std::nullptr_t v) { val = v; return *this; }

bool JsonValue::isInt()
{
	return std::holds_alternative<int>(val);
}
bool JsonValue::isBool()
{
	return std::holds_alternative<bool>(val);
}
bool JsonValue::isDouble()
{
	return std::holds_alternative<double>(val);
}
bool JsonValue::isString()
{
	return std::holds_alternative<std::string>(val);
}
bool JsonValue::isNULL()
{
	return std::holds_alternative<std::nullptr_t>(val);
}

template<typename T>
const T& JsonValue::get()
{
	return std::get<T>(val);
}
void JsonValue::get(auto&& callback)
{
	std::visit([&](const auto& arg) {callback(arg); }, val);
}

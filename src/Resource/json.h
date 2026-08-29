#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <type_traits>
#include "third_party/json.hpp"
#include "src/Common/JsonValue.h"

namespace ems_engine
{

	using json = nlohmann::json;
	namespace fs = std::filesystem;

	inline bool openJson(json& data, std::string filepath)
	{
		try
		{
			std::ifstream file(filepath);
			if (!file)
			{
				std::cout << "[ERROR]:File Can't Open(ifstream)/nFilePath:" << filepath << std::endl;
				return false;
			}
			data = json::parse(file);
			file.close();
			return true;
		}
		catch (const std::exception& e)
		{
			std::cout << "[ERROR]:" << e.what() << std::endl;
			return false;
		}
		return false;
	}

	template <typename T>
	inline bool readJson(const json& data, const json::json_pointer& js_ptr, T& value)
	{
		try
		{
			if (data.contains(js_ptr) && !data.at(js_ptr).is_null())
			{
				const auto& node = data.at(js_ptr);
				bool type_match = false;
				//bool json_value = false;
				if constexpr (std::is_same_v<T, JsonValue>)
				{
					//json_value = true;
					if (value.isInt())
					{
						if (node.is_number_integer()) value = data.at(js_ptr).get<int>();
						else if (node.is_string()) value = stoi(node.get<std::string>());
						else if (node.is_number_float()) value = static_cast<int>(node.get<float>());
						else if (node.is_boolean()) value = node.get<bool>();
						else
						{
							std::cout << "[ERROR]:Varible Type is Different! ";
							std::cout << "template is int" << std::endl;
							return false;
						}
					}
					else if (value.isDouble())
					{
						if (node.is_number_float()) value = data.at(js_ptr).get<double>();
						else if (node.is_string()) value = stof(node.get<std::string>());
						else if (node.is_number_integer())  value = static_cast<double>(node.get<int>());
						else if (node.is_boolean()) value = node.get<bool>();
						else
						{
							std::cout << "[ERROR]:Varible Type is Different! ";
							std::cout << "template is float" << std::endl;
							return false;
						}
					}
					else if (value.isString())
					{
						if (node.is_string()) value = data.at(js_ptr).get<std::string>();
						else if (node.is_number_float()) value = std::to_string(node.get<float>());
						else if (node.is_number_integer())  value = std::to_string(node.get<int>());
						else if (node.is_boolean()) { if (node.get<bool>()) value = "True"; else value = "False"; }
						else
						{
							std::cout << "[ERROR]:Varible Type is Different! ";
							std::cout << "template is string" << std::endl;
							return false;
						}
					}
					else if (value.isBool())
					{
						if (node.is_boolean()) value = data.at(js_ptr).get<bool>();
						else
						{
							std::cout << "[ERROR]:Varible Type is Different! ";
							std::cout << "template is bool" << std::endl;
							return false;
						}
					}
				}
				else if constexpr (std::is_same_v<T, int>)
				{
					if (node.is_number_integer()) type_match = true;
					else if (node.is_string()) value = stoi(node.get<std::string>());
					else if (node.is_number_float()) value = static_cast<int>(node.get<float>());
					else if (node.is_boolean()) value = node.get<bool>();
					else
					{
						std::cout << "[ERROR]:Varible Type is Different! ";
						std::cout << "template is int" << std::endl;
						return false;
					}
				}
				else if constexpr (std::is_same_v<T, float>)
				{
					if (node.is_number_float()) type_match = true;
					else if (node.is_string()) value = stof(node.get<std::string>());
					else if (node.is_number_integer())  value = static_cast<float>(node.get<int>());
					else if (node.is_boolean()) value = node.get<bool>();
					else
					{
						std::cout << "[ERROR]:Varible Type is Different! ";
						std::cout << "template is float" << std::endl;
						return false;
					}
				}
				else if constexpr (std::is_same_v<T, std::string>)
				{
					if (node.is_string()) type_match = true;
					else if (node.is_number_float()) value = std::to_string(node.get<float>());
					else if (node.is_number_integer())  value = std::to_string(node.get<int>());
					else if (node.is_boolean()) { if (node.get<bool>()) value = "True"; else value = "False"; }
					else
					{
						std::cout << "[ERROR]:Varible Type is Different! ";
						std::cout << "template is string" << std::endl;
						return false;
					}
				}
				else if constexpr (std::is_same_v<T, bool>)
				{
					if (node.is_boolean()) type_match = true;
					else
					{
						std::cout << "[ERROR]:Varible Type is Different! ";
						std::cout << "template is bool" << std::endl;
						return false;
					}
				}
				else if constexpr (std::is_same_v<T, json>)
				{
					if (node.is_object()) type_match = true;
					else
					{
						std::cout << "[ERROR]:Varible Type is Different! ";
						std::cout << "template is json" << std::endl;
						return false;
					}
				}

				if (type_match)
				{
					value = data.at(js_ptr).get<T>();
				}
				return true;

			}
		}
		catch (const json::exception& e)
		{
			std::cout << "[EXCEPTION]:" << e.id << " | " << e.what() << std::endl;
			//std::cout << "js_ptr:" << js_ptr << "value:" << value << std::endl;
			return false;
		}
		catch (const std::exception& e)
		{
			std::cout << "[EXCEPTION]:" << e.what() << std::endl;
			return false;
		}
		std::cout << "[DEBUG]:ReadJson Key Not Found - ";
		std::cout << "js_ptr:" << js_ptr << std::endl;
		return false;
	}

	template <typename T>
	inline bool writeJson(json& data, json::json_pointer ptr, T&& value)
	{
		if constexpr (std::is_same_v<std::decay_t<T>, JsonValue>)
		{
			value.get([&](const auto& arg) {data[ptr] = arg; });
		}
		else
			data[ptr] = value;
		return true;
	}
	inline bool saveJson(json& data, std::string filepath)
	{
		std::string tempPath = filepath + ".tmp";
		try
		{
			std::ofstream file(tempPath);
			if (!file.is_open())
			{
				std::cout << "[ERROR]:File Can't Open(ofstream)/nFilePath:" << tempPath << std::endl;
				return false;
			}

			file << data.dump(4);
			file.close();
			fs::path target(filepath);
			fs::path temp(tempPath);
			fs::rename(temp, target);
			return true;
		}
		catch (const std::exception& e)
		{
			std::cout << "[ERROR]:" << e.what() << std::endl;
			if (fs::exists(tempPath)) fs::remove(tempPath);
			return false;
		}
	}
}

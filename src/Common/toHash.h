#pragma once
#include <string>
#define XXH_INLINE_ALL
#include <third_party/xxhash.h>
#include <third_party/magic_enum/magic_enum.hpp>

namespace ems_engine
{
	inline uint64_t string_toHash(std::string_view str)
	{
		return XXH3_64bits(str.data(), str.size());
	}

	template<typename Enum>
	requires std::is_enum_v<Enum>
	inline uint64_t enum_toHash(Enum value)
	{
		constexpr std::string_view EnumType = magic_enum::enum_type_name<Enum>();
		std::string_view EnumValue = magic_enum::enum_name(value);
		std::string Data;
		Data.reserve(EnumType.size() + EnumValue.size());
		Data.append(EnumType).append(EnumValue);
		
		return string_toHash(Data);
	}
}
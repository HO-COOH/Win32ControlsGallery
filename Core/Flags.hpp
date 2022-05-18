#pragma once

template<typename T>
class Flags
{
	T value{};
public:
	template<typename... U>
	constexpr Flags(U... args) : value{ (static_cast<T>(args) | ...) }
	{
	}

	constexpr Flags(T value) : value{ value }
	{
	}

	constexpr operator T()
	{
		return value;
	}

	constexpr Flags operator|(Flags other)
	{
		return Flags{ value | other.value };
	}

	constexpr Flags operator&(Flags other)
	{
		return Flags{ value & other.value };
	}
};

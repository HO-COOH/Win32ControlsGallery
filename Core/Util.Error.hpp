#pragma once
#include <winerror.h>
#include <stdexcept>
#include <optional>

#define UseException
namespace Util::Error
{
	template<typename Exception = std::runtime_error, typename... Args>
	void ThrowOnError(HRESULT hr, Args&&... args)
	{
		if (SUCCEEDED(hr))
			return;
		
		if constexpr (sizeof...(args) == 0)
			throw Exception{ "Some error" };
		else
			throw Exception{ std::forward<Args>(args)... };
	}

	template<typename Ret>
	std::optional<Ret> OptionalOnError(HRESULT hr, Ret value)
	{
		return SUCCEEDED(hr) ? std::optional<Ret>{value} : std::optional<Ret>{};
	}

	void OptionalOnError(HRESULT hr)
	{
		return;
	}
}

#ifdef UseException
#define CheckRet(hr, ...) Util::Error::ThrowOnError(hr, __VA_ARGS__)
#else
#define CheckRet(hr, ...) return Util::Error::OptionalOnError(hr, __VA_ARGS__)
#endif
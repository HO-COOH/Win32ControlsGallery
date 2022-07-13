#pragma once
#include <VersionHelpers.h>
#include <cassert>

namespace Util::System
{
	/**
	 * @brief An expressive wrapper around windows version macro to determine whether the current Windows is newer than a specified version
	 * @example
	 * .cpp
	 *	if (GetVersion() >= WindowsVersion::Windows10)
	 *	{
	 *  	// do thing specifically when greater than windows 10
	 *  }
	*/
	class Version
	{
		class VersionImpl
		{
			bool(*m_versionFunction)();

		public:
			constexpr VersionImpl(bool(*versionFunction)()) : m_versionFunction(versionFunction) {}
			bool operator<(Version _) const { return !m_versionFunction(); }
			friend class Version;
		};
	public:
		bool operator>=(VersionImpl rhs) const
		{
			assert(rhs.m_versionFunction);
			return rhs.m_versionFunction();
		}

		//Versions
		static inline VersionImpl WindowsXP{ IsWindowsXPOrGreater };
		static inline VersionImpl WindowsXPSP1{ IsWindowsXPSP1OrGreater };
		static inline VersionImpl WindowsXPSP2{ IsWindowsXPSP2OrGreater };
		static inline VersionImpl WindowsXPSP3{ IsWindowsXPSP3OrGreater };
		static inline VersionImpl WindowsVista{ IsWindowsVistaOrGreater };
		static inline VersionImpl WindowsVistaSP1{ IsWindowsVistaSP1OrGreater };
		static inline VersionImpl WindowsVistaSP2{ IsWindowsVistaSP2OrGreater };
		static inline VersionImpl Windows7{ IsWindows7OrGreater };
		static inline VersionImpl Windows7SP1{ IsWindows7SP1OrGreater };
		static inline VersionImpl Windows8{ IsWindows8OrGreater };
		static inline VersionImpl Windows8_1{ IsWindows8Point1OrGreater };
		static inline VersionImpl Windows10{ IsWindows10OrGreater };
	};

	constexpr Version GetVersion() { return {}; }

	enum class Parameters
	{
		IconTitleLogFont = SPI_GETICONTITLELOGFONT,

	};
	template<Parameters param>
	auto ParametersInfoForDpi(UINT dpi);

	template<>
	inline auto ParametersInfoForDpi<Parameters::IconTitleLogFont>(UINT dpi)
	{
		LOGFONT font;
		SystemParametersInfoForDpi(static_cast<UINT>(Parameters::IconTitleLogFont), sizeof(font), &font, 0, dpi);
		return font;
	}
}
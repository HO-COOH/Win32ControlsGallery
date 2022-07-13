#pragma once
#include <wingdi.h>

namespace UI::Gdi
{
	namespace StockObject
	{
		constexpr static auto inline BlackBrush = BLACK_BRUSH;
		constexpr static auto inline DkGrayBrush = DKGRAY_BRUSH;
		constexpr static auto inline DCBrush = DC_BRUSH;
		constexpr static auto inline GrayBrush = GRAY_BRUSH;
		constexpr static auto inline LtGrayBrush = LTGRAY_BRUSH;
		constexpr static auto inline NullBrush = NULL_BRUSH;
		constexpr static auto inline WhiteBrush = WHITE_BRUSH;
		constexpr static auto inline BlackPen = BLACK_PEN;
		constexpr static auto inline DCPen = DC_PEN;
		constexpr static auto inline NullPen = NULL_PEN;
		constexpr static auto inline WhitePen = WHITE_PEN;
		constexpr static auto inline AnsiFixedFont = ANSI_FIXED_FONT;
		constexpr static auto inline AnsiVarFont = ANSI_VAR_FONT;
		constexpr static auto inline DeviceDefaultFont = DEVICE_DEFAULT_FONT;
		constexpr static auto inline DefaultGUIFont = DEFAULT_GUI_FONT;
		constexpr static auto inline OEMFixedFont = OEM_FIXED_FONT;
		constexpr static auto inline SystemFont = SYSTEM_FONT;
		constexpr static auto inline SystemFixedFont = SYSTEM_FIXED_FONT;
		constexpr static auto inline DefaultPalette = DEFAULT_PALETTE;


		template<auto stockObject>
		auto Get(); //If there is compiler error like cannot deduce "auto", then the stockObject is wrong

		template<>
		auto Get<BlackBrush>()
		{
			return static_cast<HBRUSH>(::GetStockObject(BLACK_BRUSH));
		}

		template<>
		auto Get<DkGrayBrush>()
		{
			return static_cast<HBRUSH>(::GetStockObject(DKGRAY_BRUSH));
		}

		template<>
		auto Get<DCBrush>()
		{
			return static_cast<HBRUSH>(::GetStockObject(DC_BRUSH));
		}
		
		template<>
		auto Get<GrayBrush>()
		{
			return static_cast<HBRUSH>(::GetStockObject(GRAY_BRUSH));
		}

		template<>
		auto Get<LtGrayBrush>()
		{
			return static_cast<HBRUSH>(::GetStockObject(LTGRAY_BRUSH));
		}
		
		template<>
		auto Get<NullBrush>()
		{
			return static_cast<HBRUSH>(::GetStockObject(NULL_BRUSH));
		}
		
		template<>
		auto Get<WhiteBrush>()
		{
			return static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
		}
		
		template<>
		auto Get<BlackPen>()
		{
			return static_cast<HPEN>(::GetStockObject(BLACK_PEN));
		}

		template<>
		auto Get<DCPen>()
		{
			return static_cast<HPEN>(::GetStockObject(DC_PEN));
		}

		template<>
		auto Get<NullPen>()
		{
			return static_cast<HPEN>(::GetStockObject(NULL_PEN));
		}
		
		template<>
		auto Get<WhitePen>()
		{
			return static_cast<HPEN>(::GetStockObject(WHITE_PEN));
		}
		
		template<>
		auto Get<AnsiFixedFont>()
		{
			return static_cast<HFONT>(::GetStockObject(ANSI_FIXED_FONT));
		}

		template<>
		auto Get<AnsiVarFont>()
		{
			return static_cast<HFONT>(::GetStockObject(ANSI_VAR_FONT));
		}
		
		template<>
		auto Get<DeviceDefaultFont>()
		{
			return static_cast<HFONT>(::GetStockObject(DEVICE_DEFAULT_FONT));
		}
		
		template<>
		auto Get<DefaultGUIFont>()
		{
			return static_cast<HFONT>(::GetStockObject(DEFAULT_GUI_FONT));
		}
		
		template<>
		auto Get<OEMFixedFont>()
		{
			return static_cast<HFONT>(::GetStockObject(OEM_FIXED_FONT));
		}
		
		template<>
		auto Get<SystemFont>()
		{
			return static_cast<HFONT>(::GetStockObject(SYSTEM_FONT));
		}
		
		template<>
		auto Get<SystemFixedFont>()
		{
			return static_cast<HFONT>(::GetStockObject(SYSTEM_FIXED_FONT));
		}
		
		template<>
		auto Get<DefaultPalette>()
		{
			return static_cast<HPALETTE>(::GetStockObject(DEFAULT_PALETTE));
		}
	};

	namespace Pen
	{
		enum class Style : int
		{
			Solid = PS_SOLID,
			Dash = PS_DASH,
			Dot = PS_DOT,
			DashDot = PS_DASHDOT,
			DashDotDot = PS_DASHDOTDOT,
			Null = PS_NULL,
			InsideFrame = PS_INSIDEFRAME,
		};
	}
}
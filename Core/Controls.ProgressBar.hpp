#pragma once
#include "Controls.Control.hpp"
#include <cassert>

namespace Controls
{
	class ProgressBar : public Control
	{
	public:
		//Constants
		constexpr static inline auto ClassName = PROGRESS_CLASS;

		ProgressBar(HWND parent, DWORD style, int x, int y, int width, int height)
		{
			m_hwnd = CreateWindowEx(
				0,
				ClassName,
				NULL,
				style | WS_CHILD | WS_VISIBLE,
				x, y,
				width, height,
				parent,
				NULL,
				GetModuleHandle(NULL),
				NULL
			);
		}

		enum class State
		{
			Normal = PBST_NORMAL, 
			Error = PBST_ERROR,
			Paused = PBST_PAUSED
		};

		enum class Style
		{
			Marquee = PBS_MARQUEE,
			Smooth = PBS_SMOOTH,
			SmoothReverse = PBS_SMOOTHREVERSE,
			Vertical = PBS_VERTICAL
		};

		auto deltaPos(int amount)
		{
			return static_cast<int>(sendMessage(PBM_DELTAPOS, amount, 0));
		}

		auto getBarColor()
		{
			return static_cast<COLORREF>(sendMessage(PBM_GETBARCOLOR, 0, 0));
		}

		auto setBarColor(COLORREF color)
		{
			return static_cast<COLORREF>(sendMessage(PBM_SETBARCOLOR, 0, color));
		}

		auto getBkColor()
		{
			return static_cast<COLORREF>(sendMessage(PBM_GETBKCOLOR, 0, 0));
		}

		auto setBkColor(COLORREF color)
		{
			return static_cast<COLORREF>(sendMessage(PBM_SETBKCOLOR, 0, color));
		}

		auto getPos()
		{
			return static_cast<int>(sendMessage(PBM_GETPOS, 0, 0));
		}

		auto setPos(int position)
		{
			return static_cast<int>(sendMessage(PBM_SETPOS, position, 0));
		}

		auto getRange()
		{
			PBRANGE range{};
			sendMessage(PBM_GETRANGE, 0, reinterpret_cast<LPARAM>(&range));
			return range;
		}

		auto setRange(int min, int max)
		{
			assert(min >= 0);
			return sendMessage(PBM_SETRANGE, 0, MAKELPARAM(min, max));
		}

		auto getState()
		{
			return static_cast<State>(sendMessage(PBM_GETSTATE, 0, 0));
		}

		auto setState(State state)
		{
			return static_cast<State>(sendMessage(PBM_SETSTATE, static_cast<WPARAM>(state), 0));
		}

		auto getStep()
		{
			return static_cast<int>(sendMessage(PBM_GETSTEP, 0, 0));
		}

		auto setStep(int step)
		{
			return static_cast<int>(sendMessage(PBM_SETSTEP, step, 0));
		}

		/**
		 * @brief 
		 * @return The previous position 
		*/
		auto stepIt()
		{
			return static_cast<int>(sendMessage(PBM_STEPIT, 0, 0));
		}

		void setMarquee(bool marquee, int updateTimeInMilliseconds = 30)
		{
			sendMessage(PBM_SETMARQUEE, marquee, updateTimeInMilliseconds);
		}
	};
}
#pragma once

#include <Windows.h>
#include <memory>
#include <future>
#include "Graphics.h"

namespace Gallery
{
	class SplashScreen : public std::enable_shared_from_this<SplashScreen>
	{
		static constexpr auto inline ClassName = L"SplashScreen";
		static void Register();

		HWND m_hwnd{};
		std::future<void> m_splashThread;
		std::function<void()> m_onFinish;
		static inline Graphics::Bitmap m_image;
	public:
		SplashScreen(int x, int y, int cx, int cy, int durationInMilliseconds);
		void show();

		void setImage(Graphics::Bitmap&& image);

		static Graphics::Bitmap GetImageOf(HWND hwnd);

		template<typename Function>
		void onFinish(Function&& function)
		{
			m_onFinish = std::forward<Function>(function);
		}
	};

}
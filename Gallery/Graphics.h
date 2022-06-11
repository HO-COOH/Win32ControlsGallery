#pragma once
#include <Windows.h>
#include <wingdi.h>
#include <atlbase.h>
#include <windowsx.h>
#include <wincodec.h>

namespace Graphics
{
	class Image
	{
		HANDLE m_handle{};
	public:
		enum class Type
		{
			Bitmap = IMAGE_BITMAP,
			Cursor = IMAGE_CURSOR,
			Icon = IMAGE_ICON
		};

		Image(LPCTSTR name, Type type, int cx, int cy, UINT loadFlags);

		HANDLE getHandle() const;
	};

	class Bitmap
	{
		HBITMAP m_bitmap{};
		BITMAP m_info{};
		UINT m_nWidth{};
		UINT m_nHeight{};

		void fillInfo() const;
	public:
		Bitmap() = default;
		explicit Bitmap(Image image);
		Bitmap(HBITMAP hBitmap);
		Bitmap(LPCTSTR fileName);
		~Bitmap();
		HBITMAP getHandle() const;
		
		void render(HDC hdc, int x, int y, int cx, int cy);
		operator bool() const;
		int getWidth() const;
		int getHeight() const;
		void select(HDC hdc) const;
	};
}


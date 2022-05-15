#include "pch.h"
#include "Graphics.h"
#include <string_view>
#include <wincodec.h>
#include <atlbase.h>
#include <algorithm>
#include <stdexcept>

#pragma comment(lib, "windowscodecs.lib")
extern HINSTANCE gHinst;

constexpr auto channel = 4;
auto format = GUID_WICPixelFormat32bppBGR;
BYTE* bits;
class ImageDecoder
{
	static inline CComPtr<IWICImagingFactory> m_imageFactory;
	static inline CComPtr<IWICBitmapDecoder> m_decoder;
	static inline CComPtr<IWICBitmapFrameDecode> m_frameDecode;
	static inline CComPtr<IWICBitmapSource> m_bitmapSource;
	static inline CComPtr<IWICFormatConverter> m_convertedFrame;
public:
	constexpr static wchar_t const* SupportedExtensions[]
	{
		L".png",
	};
	
	ImageDecoder(LPCTSTR name)
	{
		if (!m_imageFactory)
			m_imageFactory.CoCreateInstance(CLSID_WICImagingFactory);
		
		auto hr = m_imageFactory->CreateDecoderFromFilename(name, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &m_decoder);
		hr = m_decoder->GetFrame(0, &m_frameDecode);
		/*WICConvertBitmapSource(format, m_frameDecode, &m_bitmapSource);*/
		hr = m_imageFactory->CreateFormatConverter(&m_convertedFrame);
		hr = m_convertedFrame->Initialize(m_frameDecode, format, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
	}

	Graphics::Bitmap asBitmap()
	{
		UINT width{}, height{};
		if(FAILED(m_convertedFrame->GetSize(&width, &height)) || width == 0 || height == 0)
			throw std::runtime_error("Failed to get image size");
		width /= 5;
		height /= 5;
		
		BITMAPINFO bitmapInfo
		{
			.bmiHeader = 
			{
				.biSize = sizeof(bitmapInfo.bmiHeader),
				.biWidth = static_cast<LONG>(width),
				.biHeight = /*static_cast<LONG>(height)*/-(LONG)height,
				.biPlanes = 1,
				.biBitCount = channel * 8,
				.biCompression = BI_RGB
			}
		};
		auto const hdc = GetDC(NULL);
		void* bitmapData{};
		auto const hBitmap = CreateDIBSection(hdc, &bitmapInfo, DIB_RGB_COLORS, &bitmapData, NULL, 0);
		ReleaseDC(NULL, hdc);

		CComPtr<IWICBitmapScaler> scaler;
		auto hr = m_imageFactory->CreateBitmapScaler(&scaler);

		hr = scaler->Initialize(m_convertedFrame, width, height, WICBitmapInterpolationModeFant);
		
		if (FAILED(scaler->CopyPixels(nullptr, width * channel, width * height * channel, static_cast<BYTE*>(bitmapData))))
		{
			DeleteObject(hBitmap);
			throw std::runtime_error{ "" };
		}
		else
		{
			bits = static_cast<BYTE*>(bitmapData);
			return Graphics::Bitmap
			{ 
				hBitmap, 
				BITMAP
				{
					.bmWidth = static_cast<LONG>(width),
					.bmHeight = static_cast<LONG>(height)
				},
				&bitmapInfo
			};
		}
	}
};


Graphics::Image::Image(LPCTSTR name, Type type, int cx, int cy, UINT loadFlags)

{
	auto const extension = PathFindExtension(name);
	if (extension == nullptr)
	{
		throw std::exception("Invalid image name");
	}

		m_handle = LoadImage(gHinst, name, static_cast<UINT>(type), cx, cy, loadFlags);
}

HANDLE Graphics::Image::getHandle() const
{
	return m_handle;
}

void Graphics::Bitmap::fillInfo() const
{
	if (!m_info.bmType)
		GetObject(m_bitmap, sizeof(m_info), const_cast<BITMAP*>(&m_info));
}

Graphics::Bitmap::Bitmap(Image image) :
	m_bitmap{ static_cast<HBITMAP>(image.getHandle()) }
{
}

Graphics::Bitmap::Bitmap(LPCTSTR fileName)
{
	// Get the WIC factory from the singleton wrapper class
	pFactory.CoCreateInstance(CLSID_WICImagingFactory);

	// Create a decoder for the given image file
	pFactory->CreateDecoderFromFilename(
		fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &m_pDecoder);

	UINT nCount = 0;
	m_pDecoder->GetFrame(0, &m_pFrame);

	// Retrieve the image dimensions
	m_pFrame->GetSize(&m_nWidth, &m_nHeight);

	// Convert the format of the image frame to 32bppBGR
	pFactory->CreateFormatConverter(&m_pConvertedFrame);
	m_pConvertedFrame->Initialize(
		m_pFrame,                        // Source frame to convert
		GUID_WICPixelFormat32bppBGRA,     // The desired pixel format
		WICBitmapDitherTypeNone,         // The desired dither pattern
		NULL,                            // The desired palette 
		0.f,                             // The desired alpha threshold
		WICBitmapPaletteTypeCustom       // Palette translation type
	);
}
HBITMAP Graphics::Bitmap::getHandle() const
{
	return m_bitmap;
}

Graphics::Bitmap::Bitmap(HBITMAP bitmap)
	: m_bitmap{ bitmap }
{
}

Graphics::Bitmap::Bitmap(HBITMAP bitmap, BITMAP info, BITMAPINFO const* info2)
	: m_bitmap{ bitmap }, m_info{ info }, m_info2{*info2}
{

}

Graphics::Bitmap::~Bitmap()
{
	DeleteObject(m_bitmap);
}

void Graphics::Bitmap::render(HDC hdc, int x, int y, int cx, int cy)
{

	// Create a WIC image scaler to scale the image to the requested size
	CComPtr<IWICBitmapScaler> pScaler = nullptr;
	pFactory->CreateBitmapScaler(&pScaler);
	pScaler->Initialize(m_pConvertedFrame, cx, cy, WICBitmapInterpolationModeFant);

	// Render the image to a GDI device context
	HBITMAP hDIBBitmap = NULL;
		// Get a DC for the full screen
		HDC hdcScreen = GetDC(NULL);
		if (!hdcScreen)
			throw 1;

		BITMAPINFO bminfo;
		ZeroMemory(&bminfo, sizeof(bminfo));
		bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bminfo.bmiHeader.biWidth = cx;
		bminfo.bmiHeader.biHeight = -(LONG)cy;
		bminfo.bmiHeader.biPlanes = 1;
		bminfo.bmiHeader.biBitCount = 32;
		bminfo.bmiHeader.biCompression = BI_RGB;

		void* pvImageBits = nullptr;	// Freed with DeleteObject(hDIBBitmap)
		hDIBBitmap = CreateDIBSection(hdcScreen, &bminfo, DIB_RGB_COLORS, &pvImageBits, NULL, 0);
		if (!hDIBBitmap)
			throw 2;

		ReleaseDC(NULL, hdcScreen);

		// Calculate the number of bytes in 1 scanline
		UINT nStride = (cx * 4);
		// Calculate the total size of the image
		UINT nImage = nStride * cy;
		// Copy the pixels to the DIB section
		pScaler->CopyPixels(nullptr, nStride, nImage, reinterpret_cast<BYTE*>(pvImageBits));

		// Copy the bitmap to the target device context
		::SetDIBitsToDevice(hdc, x, y, cx, cy, 0,
			0, 0, cy, pvImageBits, &bminfo, DIB_RGB_COLORS);

		DeleteObject(hDIBBitmap);
}

Graphics::Bitmap::operator bool() const
{
	return static_cast<bool>(m_bitmap);
}

int Graphics::Bitmap::getWidth() const
{
	fillInfo();
	return m_info.bmWidth;
}

int Graphics::Bitmap::getHeight() const
{
	fillInfo();
	return m_info.bmHeight;
}

void Graphics::Bitmap::select(HDC hdc) const
{
	SelectBitmap(hdc, m_bitmap);
}

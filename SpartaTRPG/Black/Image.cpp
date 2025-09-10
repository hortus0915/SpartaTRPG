#include "Image.h"

#include "Singletons/CommonManagers.h"
#include "CommonMacros.h"

#include "MainGame.h"

#include <cmath>

Gdiplus::GdiplusStartupInput* Image::stin = nullptr;
ULONG_PTR* Image::tk = nullptr;

void Image::Init(std::wstring _fileName)
{
	std::wstring temp = L"";
	temp += DEFAULT_IMAGE_PATH;
	temp +=_fileName;
	if (!stin || !tk)
	{
		SAFE_DELETE(stin);
		SAFE_DELETE(tk);

		stin = new Gdiplus::GdiplusStartupInput;
		tk = new ULONG_PTR;

		Gdiplus::GdiplusStartup(tk, stin, 0);
	}

	SAFE_DELETE(bmp);
	SAFE_DELETE(copyBmp);

	bmp = Gdiplus::Bitmap::FromFile(temp.c_str());

	BitmapToByte();
	copyBmp = ByteToBitmap();
}

void Image::Init(std::wstring _fileName, int _posX, int _posY)
{
	Init(_fileName);

	posX = _posX;
	posY = _posY;
}

void Image::Release()
{
	SAFE_DELETE(bmp);
	SAFE_DELETE(copyBmp);

	SAFE_DELETE(stin);
	SAFE_DELETE(tk);
}

void Image::Render()
{
	SCENEMANAGER->GetMainGame()->StopDoublebuffering();
	PrintBitmap(posX, posY);
}

void Image::BitmapToByte()
{
	if (bitBytes.bytes != nullptr)
	{
		delete[] bitBytes.bytes;
		bitBytes.bytes = nullptr;
	}

	Gdiplus::Rect rect(0, 0, bmp->GetWidth(), bmp->GetHeight());
	Gdiplus::BitmapData bmpData;

	if (bmp->LockBits(&rect,
		Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeWrite,
		bmp->GetPixelFormat(), &bmpData) == Gdiplus::Ok)
	{

		int len = bmpData.Height * std::abs(bmpData.Stride);
		bitBytes.bytes = new BYTE[len];
		memcpy(bitBytes.bytes, bmpData.Scan0, len);
		bitBytes.height = bmpData.Height;
		bitBytes.width = bmpData.Width;
		bitBytes.stride = bmpData.Stride;
		bitBytes.format = bmp->GetPixelFormat();
		bmp->UnlockBits(&bmpData);
	}
}

Gdiplus::Bitmap* Image::ByteToBitmap()
{
	Gdiplus::Bitmap* bmp = new Gdiplus::Bitmap(bitBytes.width, bitBytes.height, bitBytes.stride, bitBytes.format, bitBytes.bytes);
	return bmp;
}

void Image::PrintBitmap(int posX, int posY)
{
	if (copyBmp == nullptr) return;

	HWND hwnd = GetConsoleWindow();
	HDC hdc = GetDC(hwnd);
	HDC MemoryDC = CreateCompatibleDC(hdc);
	HBITMAP hBit;
	copyBmp->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBit);
	HGDIOBJ obj = SelectObject(MemoryDC, hBit);
	BITMAP bm;
	GetObject(hBit, sizeof BITMAP, &bm);

	StretchBlt(hdc, posX, posY, bm.bmWidth, bm.bmHeight, MemoryDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	SelectObject(MemoryDC, obj);
	DeleteObject(hBit);
	DeleteDC(MemoryDC);
	ReleaseDC(hwnd, hdc);
}
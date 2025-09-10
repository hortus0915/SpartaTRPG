#pragma once

#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#pragma comment (lib, "gdiplus.lib")

#include <iostream>
#include <Windows.h>
#include <gdiplus.h>
#include <conio.h>

#define DEFAULT_IMAGE_PATH L".\\Black\\Singletons\\Images\\"

struct BITBYTE {
	INT height;
	INT width;
	INT stride;
	BYTE* bytes = nullptr;
	Gdiplus::PixelFormat format;
};

class Image
{
private:
	static Gdiplus::GdiplusStartupInput* stin;
	static ULONG_PTR* tk;

	Gdiplus::Bitmap* bmp;
	Gdiplus::Bitmap* copyBmp;
	BITBYTE bitBytes;

	int posX;
	int posY;

public:
	Image() : bmp(nullptr), copyBmp(nullptr), posX(0), posY(0) { }

	void Init(std::wstring _fileName);
	void Init(std::wstring _fileName, int _posX, int _posY);
	void Release();
	void Render();

	void BitmapToByte();
	Gdiplus::Bitmap* ByteToBitmap();
	void PrintBitmap(int posX, int posY);

	inline void SetPos(int _x, int _y) { posX = _x; posY = _y; }
	inline int GetPosX() const { return posX; }
	inline int GetPosY() const { return posY; }
};


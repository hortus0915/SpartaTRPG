#pragma once
#include <Windows.h>
#include <iostream>

#include "TextColors.h"

class DoubleBuffering {
    HANDLE hBuffer[2];
    int nScreenIndex;
    int size_x, size_y;

public:
    DoubleBuffering(int mapX, int mapY);
    ~DoubleBuffering();
    void gotoxy(int x, int y, HANDLE g_hBuffer);
    void BufferWrite(int x, int y, char* string, Color _color = ORIGINCOLOR, Color _bgColor = BLACK);
    void BufferFlipping();
    void ClearBuffer();

    void Release();

    void SetColor(Color color, Color bgcolor);
    void SetFontColor(Color color);
    void SetBgColor(Color bgcolor);
};

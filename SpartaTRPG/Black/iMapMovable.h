#pragma once

#include "BasicInterfaces.h"

#include "TextColors.h"

struct MapInfo
{
	int posX;
	int posY;

	int width;
	int height;
};

class iMapMovable : public IUpdatable, public IRenderable
{
protected:
	MapInfo info;

	char** image;

	Color charColor;
	Color bgColor;

public:
	iMapMovable(string _targetSceneName);
	virtual ~iMapMovable();

	virtual void Init(int _startX, int _startY, int _width, int _height, Color _characterColor = ORIGINCOLOR, Color _bgColor = BLACK);
	virtual void Release();

	virtual void Render() override;

	virtual void MoveTo(int _deltaX, int _deltaY);
	virtual void SetPos(int _posX, int _posY);

	virtual bool IsCanMove(int _targetX, int _targetY);

	inline Color GetCharColor() const { return charColor; }
	inline void SetCharColor(const Color& _color) { charColor = _color; }

	inline Color GetBgColor() const { return bgColor; }
	inline void SetBgColor(const Color& _color) { bgColor = _color; }
};


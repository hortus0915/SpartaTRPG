#pragma once

#include "BasicInterfaces.h"

#include "TextColors.h"

class MapData;

class iMapMovable : public IUpdatable, public IRenderable
{
protected:

	int posX;
	int posY;

	MapData* mapData;

	char** image;
	Color charColor;
	Color bgColor;

	bool isNewRender = false;

public:
	iMapMovable(string _targetSceneName, MapData* _mapData);
	virtual ~iMapMovable();

	virtual void Init(Color _characterColor = ORIGINCOLOR, Color _bgColor = BLACK);
	virtual void Release();

	virtual void Render() override;

	virtual void MoveTo(int _deltaX, int _deltaY);
	virtual void SetPos(int _posX, int _posY);
	virtual void MapImageSet();

	virtual bool IsCanMove(int _targetX, int _targetY);

	inline Color GetCharColor() const { return charColor; }
	inline void SetCharColor(const Color& _color) { charColor = _color; }

	inline Color GetBgColor() const { return bgColor; }
	inline void SetBgColor(const Color& _color) { bgColor = _color; }
};


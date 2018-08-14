#pragma once
#include <wincodec.h>
#include "Graphic.h"

class SpriteSheet
{
private:
	Graphic * gfx;
	ID2D1Bitmap *bmp;
public:
	SpriteSheet(const wchar_t *filename, Graphic *gfx);
	~SpriteSheet();
	void Draw();
};


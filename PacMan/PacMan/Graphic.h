#pragma once
#include <d2d1.h>
#include <Windows.h>
#include <Dwrite.h>

class Graphic
{
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;
	ID2D1SolidColorBrush*Brush;
	HRESULT hres;

	IDWriteFactory* pDWriteFactory_;
	IDWriteTextFormat* pTextFormat_;

    const wchar_t* wszText_;
	UINT32 cTextLength_;

public:
	Graphic();
	~Graphic();
	bool Init(HWND hwnd);
	ID2D1RenderTarget*GetRenderTarget() {
		return rendertarget;
	}
	void BeginDraw() { rendertarget->BeginDraw(); }
	void EndDraw() { rendertarget->EndDraw(); }
	void ClearScreen(float r, float g, float b);
	void DrawCircle(float size ,float x, float y, float radius, float r, float g, float b);
	void DrawRectangle(float size ,float left, float top, float right, float buttom, float r, float g, float b);
	void DrawText(const wchar_t* wszText_, int text_size, int left, int top, int right, int bottom, float r, float g, float b);
};


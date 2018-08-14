#pragma once
#include <d2d1.h>
#include <Windows.h>

class Graphic
{
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* rendertarget;
	ID2D1SolidColorBrush*Brush;
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
	void DrawCircle(float x, float y, float radius, float r, float g, float b);
	void DrawRectangle(float left, float top, float right, float buttom, float r, float g, float b);
};


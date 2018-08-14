#include "stdafx.h"
#include "Graphic.h"


Graphic::Graphic()
{
	rendertarget = NULL;
	factory = NULL;

}


Graphic::~Graphic()
{
	if (rendertarget)rendertarget->Release();
	if (factory)factory->Release();
}

bool Graphic::Init(HWND hwnd)
{
	HRESULT hres = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);
	if (hres != S_OK) return false;
	RECT rect;
	GetClientRect(hwnd, &rect);
	hres = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rect.right, rect.bottom)),
		&rendertarget
	);
	if (hres != S_OK) return false;
	return true;
}

void Graphic::ClearScreen(float r, float g, float b)
{
	rendertarget->Clear(D2D1::ColorF(r, g, b));
}

void Graphic::DrawCircle(float x, float y, float radius, float r, float g, float b)
{
	ID2D1SolidColorBrush *brush;
	rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &brush);
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, 5.0f);
	brush->Release();
}

void Graphic::DrawRectangle(float left, float top, float right, float buttom, float r, float g, float b)
{
	ID2D1SolidColorBrush *brush;
	rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &brush);
	rendertarget->DrawRectangle(D2D1::Rect(left, top, right, buttom), brush, 5.0f);
	brush->Release();
}

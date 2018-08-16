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
	hres = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

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

void Graphic::DrawCircle(float size ,float x, float y, float radius, float r, float g, float b)
{
	ID2D1SolidColorBrush *brush;
	rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &brush);
	rendertarget->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(x, y), radius, radius), brush, size);
	brush->Release();
}

void Graphic::DrawRectangle(float size ,float left, float top, float right, float buttom, float r, float g, float b)
{
	ID2D1SolidColorBrush *brush;
	rendertarget->CreateSolidColorBrush(D2D1::ColorF(r, g, b), &brush);
	rendertarget->DrawRectangle(D2D1::Rect(left, top, right, buttom), brush, size);
	brush->Release();
}

void Graphic::DrawText(const wchar_t* wszText_, int text_size, int left, int top, int right, int bottom, float r, float g, float b)
{
	if (SUCCEEDED(hres))
	{
		hres = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pDWriteFactory_)
		);
	}

	cTextLength_ = (UINT32)wcslen(wszText_);

	if (SUCCEEDED(hres))
	{
		hres = pDWriteFactory_->CreateTextFormat(
			TEXT("Gabriola"),                // Font family name.
			NULL,                       // Font collection (NULL sets it to use the system font collection).
			DWRITE_FONT_WEIGHT_REGULAR,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			text_size,
			TEXT("en-us"),
			&pTextFormat_
		);
	}

	// Center align (horizontally) the text.
	if (SUCCEEDED(hres))
	{
		hres = pTextFormat_->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
	}

	if (SUCCEEDED(hres))
	{
		hres = pTextFormat_->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}

	ID2D1SolidColorBrush *brush;
	rendertarget->CreateSolidColorBrush(D2D1::ColorF(r,g,b), &brush);

	D2D1_RECT_F layoutRect = D2D1::RectF(
		static_cast<FLOAT>(left),
		static_cast<FLOAT>(top),
		static_cast<FLOAT>(right),
		static_cast<FLOAT>(bottom)
	);
	rendertarget->DrawText(
		wszText_,        // The string to render.
		cTextLength_,    // The string's length.
		pTextFormat_,    // The text format.
		layoutRect,       // The region of the window where the text will be rendered.
		brush     // The brush used to draw the text.
	);
}

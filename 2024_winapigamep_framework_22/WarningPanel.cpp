#include "pch.h"
#include "WarningPanel.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "GDISelector.h"

WarningPanel::WarningPanel(float fadeTime, Vec2 pos, Vec2 size)
{
	_fadeValue = 128;
	_deltaTime = 0;
	_fadeTime = fadeTime;
	SetPos(pos);
	SetSize(size);
}

void WarningPanel::Update()
{
	if (isFade)
	{
		_deltaTime += fDT;
		float elapseTime = _deltaTime / _fadeTime;
		_fadeValue = std::lerp(0, 255, elapseTime);

		if (elapseTime >= 1)
			GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void WarningPanel::Render(HDC _hdc)
{
	HDC alphaDC = CreateCompatibleDC(_hdc);
	HBITMAP alphaBit = CreateCompatibleBitmap(_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(alphaDC, alphaBit);

	BitBlt(alphaDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _hdc, 0, 0, SRCCOPY);

	GDISelector brush(_hdc, BRUSH_TYPE::RED);
	GDISelector pen(_hdc, PEN_TYPE::HOLLOW);

	Vec2 vPos = GetPos();
	Vec2 vScale = GetSize();

	bf.SourceConstantAlpha = _fadeValue;

	RECT_RENDER(_hdc, vPos.x, vPos.y, vScale.x, vScale.y);
	AlphaBlend(_hdc, (int)(vPos.x - vScale.x / 2), (int)(vPos.y - vScale.y / 2), vScale.x, vScale.y
		, alphaDC, 0, 0, vScale.x, vScale.y, bf);

	DeleteObject(alphaBit);
	DeleteDC(alphaDC);
}

#include "pch.h"
#include "WarningPanel.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "GDISelector.h"
#include "SceneManager.h"
#include "Scene.h"

WarningPanel::WarningPanel(float fadeTime, Vec2 pos, Vec2 size, bool isCenter)
{
	_deltaTime = 0;
	_fadeTime = fadeTime;
	_fadeValue = 128;
	this->isCenter = isCenter;
	SetPos(pos);
	SetSize(size);
}

WarningPanel::~WarningPanel()
{
	DCRealase();
}

void WarningPanel::Update()
{
	if (isFade)
	{
		_deltaTime += fDT;
		float elapseTime = _deltaTime / _fadeTime;
		_fadeValue = std::lerp(128, 255, elapseTime);

		if (elapseTime >= 1)
			GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void WarningPanel::Render(HDC _hdc)
{
	if(isRotate)
		RotateBlt(_hdc);
	else
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetSize();
		float halfWidth = vScale.x / 2.0f;
		float halfHeight = vScale.y / 2.0f;

		DCInit(_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
		BitBlt(alphaDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, _hdc, 0, 0, SRCCOPY);

		GDISelector brush(_hdc, BRUSH_TYPE::RED);
		GDISelector pen(_hdc, PEN_TYPE::HOLLOW);
		RECT_RENDER(_hdc, vPos.x, vPos.y, vScale.x, vScale.y);

		bf.SourceConstantAlpha = _fadeValue;
		AlphaBlend(_hdc, (int)(vPos.x - halfWidth), (int)(vPos.y - halfHeight), vScale.x, vScale.y
			, alphaDC, 0, 0, vScale.x, vScale.y, bf);
	}
}

void WarningPanel::RotateBlt(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetSize();
	float halfWidth = vScale.x / 2.0f;
	float halfHeight = vScale.y / 2.0f;
	float dcWidth = SCREEN_WIDTH + vScale.x;
	float dcHeight = SCREEN_HEIGHT + vScale.y;

	DCInit(_hdc, dcWidth, dcHeight);
	BitBlt(alphaDC, 0, 0, dcWidth, dcHeight, _hdc, 0, 0, SRCCOPY);

	GDISelector brush(alphaDC, BRUSH_TYPE::RED);
	GDISelector pen(alphaDC, PEN_TYPE::HOLLOW);
	RECT_RENDER(alphaDC, vPos.x, vPos.y, vScale.x, vScale.y);

	bf.SourceConstantAlpha = _fadeValue;
	AlphaBlend(alphaDC, (int)(vPos.x - halfWidth), (int)(vPos.y - halfHeight), vScale.x, vScale.y
		, alphaDC, 0, 0, vScale.x, vScale.y, bf);

	float cos = cosf(_angle);
	float sin = sinf(_angle);

	POINT vertices[4];

	// 회전 중심 좌표
	float centerX = vPos.x; // 왼쪽 끝의 X 좌표
	float centerY = vPos.y;           // Y 좌표는 그대로 유지

	// 각 꼭짓점 회전 후 화면 좌표 계산
	if (!isCenter)
	{
		centerX -= halfWidth;
		vertices[0].x = (LONG)(centerX + (0 * cos - (-halfHeight) * sin));
		vertices[0].y = (LONG)(centerY + (0 * sin + (-halfHeight) * cos));

		vertices[1].x = (LONG)(centerX + (vScale.x * cos - (-halfHeight) * sin));
		vertices[1].y = (LONG)(centerY + (vScale.x * sin + (-halfHeight) * cos));

		vertices[2].x = (LONG)(centerX + (0 * cos - (halfHeight)*sin));
		vertices[2].y = (LONG)(centerY + (0 * sin + (halfHeight)*cos));
	}
	else
	{
		vertices[0].x = (LONG)(centerX + (-halfWidth * cos - halfHeight * sin));
		vertices[0].y = (LONG)(centerY + (-halfWidth * sin + halfHeight * cos));

		vertices[1].x = (LONG)(centerX + (halfWidth * cos - halfHeight * sin));
		vertices[1].y = (LONG)(centerY + (halfWidth * sin + halfHeight * cos));

		vertices[2].x = (LONG)(centerX + (-halfWidth * cos + halfHeight * sin));
		vertices[2].y = (LONG)(centerY + (-halfWidth * sin - halfHeight * cos));
	}

	AlphaBlend(alphaDC, (int)(vPos.x - halfWidth), (int)(vPos.y - halfHeight), vScale.x, vScale.y
		, alphaDC, 0, 0, vScale.x, vScale.y, bf);
	BitBlt(rotateDC, 0, 0, dcWidth, dcHeight, alphaDC, 0, 0, SRCCOPY);
	PlgBlt(_hdc, vertices, rotateDC, (int)(vPos.x - halfWidth), (int)(vPos.y - halfHeight), vScale.x, vScale.y, NULL, 0, 0);
}

void WarningPanel::DCInit(HDC hdc, int width, int height)
{
	if (alphaDC == NULL) {
		alphaDC = CreateCompatibleDC(hdc);
		alphaBit = CreateCompatibleBitmap(hdc, width, height);
		SelectObject(alphaDC, alphaBit);
	}
	if (rotateDC == NULL) {
		rotateDC = CreateCompatibleDC(hdc);
		rotateBit = CreateCompatibleBitmap(hdc, width, height);
		SelectObject(rotateDC, rotateBit);
	}
}

void WarningPanel::DCRealase()
{
	if (alphaDC)
	{
		DeleteObject(alphaBit);
		DeleteDC(alphaDC);
	}
	if (rotateDC)
	{
		DeleteObject(rotateBit);
		DeleteDC(rotateDC);
	}
}

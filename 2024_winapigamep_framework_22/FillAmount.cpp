#include "pch.h"
#include "FillAmount.h"

FillAmount::FillAmount()
{
}

void FillAmount::Update()
{
}

void FillAmount::Render(HDC _hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(_hdc, brush);

	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);
	ComponentRender(_hdc);

	SelectObject(_hdc, oldbrush);
}

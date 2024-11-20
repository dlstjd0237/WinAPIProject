#include "pch.h"
#include "UI_Health.h"

UI_Health::UI_Health() : m_fFillAmount(1.f) // 초기 FillAmount는 1 (100%)
{
}

void UI_Health::SetFillAmount(float _amount)
{
    // 비율 제한 (0 ~ 1)
    if (_amount < 0.f) _amount = 0.f;
    if (_amount > 1.f) _amount = 1.f;
    m_fFillAmount = _amount;
}

void UI_Health::Update()
{
}

void UI_Health::Render(HDC _hdc)
{
    Vec2 vPos = GetPos();
    Vec2 vSize = GetSize();

    // 전체 크기 Rect
    RECT rectFull = {
        vPos.x,
        vPos.y,
        (vPos.x + vSize.x),
        (vPos.y + vSize.y)
    };

    // FillAmount에 따른 부분 Rect
    RECT rectFill = {
        vPos.x,
        vPos.y,
        (vPos.x + vSize.x * m_fFillAmount),
        (vPos.y + vSize.y)
    };

    // 배경 그리기 (예: 빈 체력 바)
    HBRUSH hBrushBg = CreateSolidBrush(RGB(100, 100, 100)); // 회색 배경
    FillRect(_hdc, &rectFull, hBrushBg);
    DeleteObject(hBrushBg);

    // 체력 부분 그리기 (예: 초록색 채워진 부분)
    HBRUSH hBrushFill = CreateSolidBrush(RGB(255, 0, 0)); // 초록색
    FillRect(_hdc, &rectFill, hBrushFill);
    DeleteObject(hBrushFill);

    // 컴포넌트 렌더링
    ComponentRender(_hdc);
}

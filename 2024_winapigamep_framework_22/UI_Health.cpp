#include "pch.h"
#include "UI_Health.h"
#include "ResourceManager.h"

UI_Health::UI_Health(const std::wstring& bgPath, const std::wstring& fillPath) 
    : m_fFillAmount(1.f) // 초기 FillAmount는 1 (100%)
{
    // 배경과 FillAmount 이미지를 로드
    m_pBgTex = GET_SINGLE(ResourceManager)->TextureLoad(L"HealthBarBg", bgPath.c_str());
    m_pFillTex = GET_SINGLE(ResourceManager)->TextureLoad(L"HealthBarFill", fillPath.c_str());
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

    // 배경 이미지 렌더링
    int bgWidth = m_pBgTex->GetWidth();
    int bgHeight = m_pBgTex->GetHeight();
    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgWidth / 2),
        (int)(vPos.y - bgHeight / 2),
        bgWidth, bgHeight,
        m_pBgTex->GetTexDC(),
        0, 0, bgWidth, bgHeight, RGB(255, 0, 255));

    // FillAmount 이미지 렌더링 (비율에 따라 크기 조정)
    int fillWidth = (int)(m_pFillTex->GetWidth() * m_fFillAmount); // FillAmount에 따라 너비 결정
    int fillHeight = m_pFillTex->GetHeight();
    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgWidth / 2),  // 시작 위치는 배경과 동일
        (int)(vPos.y - bgHeight / 2),
        fillWidth, fillHeight,       // 너비는 FillAmount로 조정
        m_pFillTex->GetTexDC(),
        0, 0, fillWidth, fillHeight, RGB(255, 255, 255));

    // 컴포넌트 렌더링
    ComponentRender(_hdc);

#pragma region notUse

    //Vec2 vPos = GetPos();
    //Vec2 vSize = GetSize();

    //// 전체 크기 Rect
    //RECT rectFull = {
    //    vPos.x,
    //    vPos.y,
    //    (vPos.x + vSize.x),
    //    (vPos.y + vSize.y)
    //};

    //// FillAmount에 따른 부분 Rect
    //RECT rectFill = {
    //    vPos.x,
    //    vPos.y,
    //    (vPos.x + vSize.x * m_fFillAmount),
    //    (vPos.y + vSize.y)
    //};

    //// 배경 그리기 (예: 빈 체력 바)
    //HBRUSH hBrushBg = CreateSolidBrush(RGB(100, 100, 100)); // 회색 배경
    //FillRect(_hdc, &rectFull, hBrushBg); //rect를 토대로 가져온 브러쉬와 dc를 이용해 그려주기
    //DeleteObject(hBrushBg);  //브러쉬는 쓰고나서 지워줘야한다.

    //// 체력 부분 그리기 (예: 초록색 채워진 부분)
    //HBRUSH hBrushFill = CreateSolidBrush(RGB(255, 0, 0)); // 초록색
    //FillRect(_hdc, &rectFill, hBrushFill);
    //DeleteObject(hBrushFill);

#pragma endregion
}

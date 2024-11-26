#include "pch.h"
#include "UI_Health.h"
#include "ResourceManager.h"

UI_Health::UI_Health() : m_fFillAmount(1.f) // 초기 FillAmount는 1 (100%)
{
    // 배경과 FillAmount 이미지를 로드
    m_pBgTex = GET_SINGLE(ResourceManager)->TextureLoad(L"HealthBarBg", L"Texture\\plane.bmp");
    m_pFillTex = GET_SINGLE(ResourceManager)->TextureLoad(L"HealthBarFill", L"Texture\\Bullet.bmp");
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
        0, 0, fillWidth, fillHeight, RGB(255, 0, 255));

    // 컴포넌트 렌더링
    ComponentRender(_hdc);
}

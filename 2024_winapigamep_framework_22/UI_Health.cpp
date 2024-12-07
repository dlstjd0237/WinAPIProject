#include "pch.h"
#include "UI_Health.h"
#include "ResourceManager.h"

UI_Health::UI_Health(wstring bgPath, wstring fillPath, wstring Bgname, wstring amountName, 
    Vec2 Scale)
    : m_fFillAmount(1.f), // 초기 FillAmount는 1 (100%)
    m_bgpath(bgPath),
    m_Amountpath(fillPath),
    m_bgName(Bgname),
    m_AmountName(amountName),
    m_scale(Scale)

{
    // 배경과 FillAmount 이미지를 로드
    m_pBgTex = GET_SINGLE(ResourceManager)->TextureLoad(m_bgName, m_bgpath);
    m_pFillTex = GET_SINGLE(ResourceManager)->TextureLoad(m_AmountName, m_Amountpath);
}

UI_Health::~UI_Health()
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

    // 배경이미지를 GeWidth, Height함수를 통해 가져온다
    int bgWidth = m_pBgTex->GetWidth();
    int bgHeight = m_pBgTex->GetHeight();
    
    //가져온 크기에서 스케일만큼 곱한다.
    int bgScaledWidth = (int)(bgWidth * m_scale.x);
    int bgScaledHeight = (int)(bgHeight * m_scale.y);

    //255,0,255 RGD값을 투명하게 처리하고 
    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgScaledWidth / 2),
        (int)(vPos.y - bgScaledHeight / 2),
        bgScaledWidth, bgScaledHeight, // 확대/축소된 크기로 렌더링
        m_pBgTex->GetTexDC(),
        0, 0, bgWidth, bgHeight, // 원본 크기 사용
        RGB(255, 0, 255));

    // FillAmount 이미지 렌더링 (비율에 따라 크기 조정)
    int fillWidth = (int)(m_pFillTex->GetWidth() * m_fFillAmount);
    int fillHeight = m_pFillTex->GetHeight();

    // Scale을 적용한 Fill 크기 계산
    int fillScaledWidth = (int)(fillWidth * m_scale.x);
    int fillScaledHeight = (int)(fillHeight * m_scale.y);

    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgScaledWidth / 2), // 배경과 동일한 위치
        (int)(vPos.y - bgScaledHeight / 2),
        fillScaledWidth, fillScaledHeight, // 확대/축소된 크기로 렌더링
        m_pFillTex->GetTexDC(),
        0, 0, fillWidth, fillHeight, // FillAmount에 따른 원본 크기
        RGB(255, 0, 255));

    // 컴포넌트 렌더링
    ComponentRender(_hdc);
}
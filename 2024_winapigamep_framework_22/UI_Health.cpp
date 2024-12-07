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

    //BG배경 이미지 렌더링 ==============================================

    // 배경이미지를 GeWidth, Height함수를 통해 가져온다
    int bgWidth = m_pBgTex->GetWidth();
    int bgHeight = m_pBgTex->GetHeight();
    
    //가져온 크기에서 스케일만큼 곱한다.
    int bgScaledWidth = (int)(bgWidth * m_scale.x);
    int bgScaledHeight = (int)(bgHeight * m_scale.y);

    //255,0,255 RGD값을 투명하게 처리하고 크기를 스케일을 연산한 값에 기준하여 한다.
    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgScaledWidth / 2),
        (int)(vPos.y - bgScaledHeight / 2),
        bgScaledWidth, bgScaledHeight,
        m_pBgTex->GetTexDC(),
        0, 0, bgWidth, bgHeight,
        RGB(255, 0, 255));


    // FillAmount 이미지 렌더링 ==============================================

    //넓이에 경우, FillAmount값에 따라 달라져야하므로 m_fFillAmount변수를 곱해준다(0 ~ 1)
    int fillWidth = (int)(m_pFillTex->GetWidth() * m_fFillAmount);
    int fillHeight = m_pFillTex->GetHeight();

    // 위와같다
    int fillScaledWidth = (int)(fillWidth * m_scale.x);
    int fillScaledHeight = (int)(fillHeight * m_scale.y);

    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgScaledWidth / 2),
        (int)(vPos.y - bgScaledHeight / 2),
        fillScaledWidth, fillScaledHeight, 
        m_pFillTex->GetTexDC(),
        0, 0, fillWidth, fillHeight,
        RGB(255, 0, 255));

    // 컴포넌트 렌더링, 필요없나???
    ComponentRender(_hdc);
}
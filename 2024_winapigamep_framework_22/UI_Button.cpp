#include "pch.h"
#include "UI_Button.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Texture.h"

UI_Button::UI_Button(std::wstring bgPath, std::wstring text, Vec2 _scale) :
    m_text(text),
    m_pBgTex(nullptr),
    m_scale(_scale)
{
    m_pBgTex = GET_SINGLE(ResourceManager)->TextureLoad(L"ButtonBg", bgPath);
}

void UI_Button::Update()
{
    // 마우스 위치 가져오기
    Vec2 mousePos = GET_SINGLE(InputManager)->GetMousePos();

    Vec2 vPos = GetPos(); // 버튼 중심 위치
    int bgWidth = m_pBgTex->GetWidth();   // 배경 이미지 너비
    int bgHeight = m_pBgTex->GetHeight(); // 배경 이미지 높이

    int bgUpscaleWidth = bgWidth * m_scale.x;
    int bgUpscaleHeight = bgHeight * m_scale.y;

    // 버튼 영역 안에 있는지 확인
    bool isMouseOver = (mousePos.x >= vPos.x - bgUpscaleWidth / 2 &&
        mousePos.x <= vPos.x + bgUpscaleWidth / 2 &&
        mousePos.y >= vPos.y - bgUpscaleHeight / 2 &&
        mousePos.y <= vPos.y + bgUpscaleHeight / 2);

    if (isMouseOver && GET_SINGLE(InputManager)->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN) // 마우스 왼쪽 버튼이 눌렸는지 확인
    {
        std::cout << "AAAA" << std::endl;
        if (OnClick)
        {
            OnClick();
        }
    }
}

void UI_Button::Render(HDC _hdc)
{
    Vec2 vPos = GetPos(); // 버튼 중심 위치
    int bgWidth = m_pBgTex->GetWidth();   // 배경 이미지 너비
    int bgHeight = m_pBgTex->GetHeight(); // 배경 이미지 높이

    int bgUpscaleWidth = bgWidth * m_scale.x;
    int bgUpscaleHeight = bgHeight * m_scale.y;

    //// 가장자리 빨간색 경계선 그리기
    //HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // 빨간색 펜 생성
    //HGDIOBJ hOldPen = SelectObject(_hdc, hPen);

    //// 사각형 경계선 그리기
    //Rectangle(
    //    _hdc,
    //    (int)(vPos.x - bgWidth / 2), (int)(vPos.y - bgHeight / 2),
    //    (int)(vPos.x + bgWidth / 2), (int)(vPos.y + bgHeight / 2)
    //);

    //// 이전 펜으로 복원하고 새 펜 삭제
    //SelectObject(_hdc, hOldPen);
    //DeleteObject(hPen);

    // 배경 이미지 렌더링
    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgUpscaleWidth / 2),
        (int)(vPos.y - bgUpscaleHeight / 2),
        bgUpscaleWidth, bgUpscaleHeight,
        m_pBgTex->GetTexDC(),
        0, 0, bgWidth, bgHeight, RGB(255, 0, 255));

    //텍스트 만들기
    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(0, 0, 0));
    RECT rect = { (int)(vPos.x - bgWidth / 2), (int)(vPos.y - bgHeight / 2), 
        (int)(vPos.x + bgWidth / 2), (int)(vPos.y + bgHeight / 2) };
    DrawText(_hdc, m_text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

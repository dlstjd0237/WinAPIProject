#include "pch.h"
#include "UI_Button.h"
#include "InputManager.h"
#include "ResourceManager.h"

UI_Button::UI_Button(const std::wstring& bgPath)
{
    m_pBgTex = GET_SINGLE(ResourceManager)->TextureLoad(L"ButtonBg", bgPath.c_str());
}

void UI_Button::Update()
{
    // 마우스 위치 가져오기
    Vec2 mousePos = GET_SINGLE(InputManager)->GetMousePos();

    Vec2 vPos = GetPos(); // 버튼 중심 위치
    int bgWidth = m_pBgTex->GetWidth();   // 배경 이미지 너비
    int bgHeight = m_pBgTex->GetHeight(); // 배경 이미지 높이

    // 버튼 영역 안에 있는지 확인
    bool isMouseOver = (mousePos.x >= vPos.x - bgWidth / 2 &&
        mousePos.x <= vPos.x + bgWidth / 2 &&
        mousePos.y >= vPos.y - bgHeight / 2 &&
        mousePos.y <= vPos.y + bgHeight / 2);

    if (isMouseOver && GET_SINGLE(InputManager)->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN) // 마우스 왼쪽 버튼이 눌렸는지 확인
    {
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

    // 가장자리 빨간색 경계선 그리기
    HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0)); // 빨간색 펜 생성
    HGDIOBJ hOldPen = SelectObject(_hdc, hPen);

    // 사각형 경계선 그리기
    Rectangle(
        _hdc,
        (int)(vPos.x - bgWidth / 2), (int)(vPos.y - bgHeight / 2),
        (int)(vPos.x + bgWidth / 2), (int)(vPos.y + bgHeight / 2)
    );

    // 이전 펜으로 복원하고 새 펜 삭제
    SelectObject(_hdc, hOldPen);
    DeleteObject(hPen);

    // 배경 이미지 렌더링
    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgWidth / 2),
        (int)(vPos.y - bgHeight / 2),
        bgWidth, bgHeight,
        m_pBgTex->GetTexDC(),
        0, 0, bgWidth, bgHeight, RGB(255, 0, 255));
}
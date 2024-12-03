#include "pch.h"
#include "UI_Button.h"
#include "InputManager.h"

UI_Button::UI_Button(const std::wstring& bgPath)
{
	m_pBgTex = GET_SINGLE(ResourceManager)->TextureLoad(L"HealthBarBg", bgPath.c_str());
}

void UI_Button::Update()
{
    Vec2 mousePos = GET_SINGLE(InputManager)->GetMousePos();

    Vec2 vPos = GetPos();
    Vec2 vSize = GetSize();

    // 버튼 영역 안에 있는지 확인
    bool isMouseOver = (mousePos.x >= vPos.x - vSize.x / 2 &&
        mousePos.x <= vPos.x + vSize.x / 2 &&
        mousePos.y >= vPos.y - vSize.y / 2 &&
        mousePos.y <= vPos.y + vSize.y / 2);

    // 클릭 이벤트 처리
    if (isMouseOver && GET_SINGLE(InputManager)->GetKey(KEY_TYPE::DOWN)) // IsMouseDown: 마우스 왼쪽 버튼 확인
    {
        std::cout << "Clicked!!" << std::endl;
    }
}

void UI_Button::Render(HDC _hdc)
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
}

void UI_Button::SetFillAmount(float _amount)
{
}

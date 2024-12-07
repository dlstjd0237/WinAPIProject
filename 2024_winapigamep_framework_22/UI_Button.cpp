#include "pch.h"
#include "UI_Button.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Texture.h"

UI_Button::UI_Button(std::wstring bgPath, std::wstring text, Vec2 _scale, std::wstring _name, Vec2 textScale, bool _isoutline) :
    m_texturName(_name),
    m_texturPath(bgPath),
    m_text(text),
    m_pBgTex(nullptr),
    m_scale(_scale),
    m_textScale(textScale),
    isMouseOverOutline(true)
{
    m_pBgTex = GET_SINGLE(ResourceManager)->TextureLoad(m_texturName, m_texturPath);
    isOutLine = _isoutline;
}

UI_Button::~UI_Button()
{

}

void UI_Button::Update()
{
    // 마우스 위치 가져오기
    Vec2 mousePos = GET_SINGLE(InputManager)->GetMousePos();
    Vec2 vPos = GetPos();

    //이미지 넓이 가져오기
    int bgWidth = m_pBgTex->GetWidth();  
    int bgHeight = m_pBgTex->GetHeight(); 

    //스케일 연산
    int bgUpscaleWidth = bgWidth * m_scale.x;
    int bgUpscaleHeight = bgHeight * m_scale.y;

    // 버튼 영역 안에 있는지 확인
    bool isMouseOver = (mousePos.x >= vPos.x - bgUpscaleWidth / 2 &&
        mousePos.x <= vPos.x + bgUpscaleWidth / 2 &&
        mousePos.y >= vPos.y - bgUpscaleHeight / 2 &&
        mousePos.y <= vPos.y + bgUpscaleHeight / 2);

    // 클릭처리
    if (isMouseOver && GET_SINGLE(InputManager)->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN) // 마우스 왼쪽 버튼이 눌렸는지 확인
    {
        if (OnClick)
        {
            OnClick();
        }
    }
    
    //아웃라인 표시설정
    else if (isMouseOver && isOutLine)
    {
        isMouseOverOutline = true;
    }
    else
    {
        isMouseOverOutline = false;
    }
}

void UI_Button::Render(HDC _hdc)
{
    Vec2 vPos = GetPos(); // 버튼 중심 위치

    int bgWidth = m_pBgTex->GetWidth();   // 배경 이미지 넓이
    int bgHeight = m_pBgTex->GetHeight(); 

    int bgUpscaleWidth = bgWidth * m_scale.x;   //스케일 계산
    int bgUpscaleHeight = bgHeight * m_scale.y;

    // 아웃라인그리기
    if (isMouseOverOutline)
    {
        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
        HGDIOBJ hOldPen = SelectObject(_hdc, hPen);
        Rectangle(
            _hdc,
            (int)(vPos.x - bgUpscaleWidth / 2 + 1), (int)(vPos.y - bgUpscaleHeight / 2 + 1),
            (int)(vPos.x + bgUpscaleWidth / 2), (int)(vPos.y + bgUpscaleHeight / 2)
        );
        SelectObject(_hdc, hOldPen);
        DeleteObject(hPen);
    }

    // 배경 이미지 렌더링
    ::TransparentBlt(
        _hdc,
        (int)(vPos.x - bgUpscaleWidth / 2),
        (int)(vPos.y - bgUpscaleHeight / 2),
        bgUpscaleWidth, bgUpscaleHeight,
        m_pBgTex->GetTexDC(),
        0, 0, bgWidth, bgHeight, RGB(255, 0, 255));

    //텍스트 ==========================================

    // 텍스트 크기 적용
    HFONT hFont = CreateFont(
        (int)(20 * m_textScale.y), // 높이 (배율 적용)
        0,                        // 폭
        0,                        // 기울기 각도
        0,                        // 기준선 기울기 각도
        FW_NORMAL,                // 굵기
        FALSE,                    // 이탤릭
        FALSE,                    // 밑줄
        FALSE,                    // 취소선
        DEFAULT_CHARSET,          // 문자 집합
        OUT_DEFAULT_PRECIS,       // 출력 정밀도
        CLIP_DEFAULT_PRECIS,      // 클리핑 정밀도
        DEFAULT_QUALITY,          // 출력 품질
        DEFAULT_PITCH | FF_SWISS, // 글꼴 유형
        L"Arial");                // 글꼴 이름

    HFONT hOldFont = (HFONT)SelectObject(_hdc, hFont);

    // 텍스트 그리기
    SetBkMode(_hdc, TRANSPARENT);
    SetTextColor(_hdc, RGB(0, 0, 0));
    RECT rect = {
    (int)(vPos.x - bgUpscaleWidth / 2),  // 버튼의 왼쪽
    (int)(vPos.y - bgUpscaleHeight / 2), // 버튼의 위쪽
    (int)(vPos.x + bgUpscaleWidth / 2),  // 버튼의 오른쪽
    (int)(vPos.y + bgUpscaleHeight / 2)  // 버튼의 아래쪽
    };

    DrawText(_hdc, m_text.c_str(), -1, &rect, DT_CENTER | DT_VCENTER);

    SelectObject(_hdc, hOldFont);
    DeleteObject(hFont);
}

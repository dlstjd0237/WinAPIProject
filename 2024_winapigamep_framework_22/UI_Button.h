#pragma once
#include "Object.h"
#include "Texture.h"
#include <string>;
#include <functional>

class UI_Button : public Object
{
public:
	UI_Button( std::wstring bgPath,  std::wstring text, Vec2 _scale);
	std::function<void()> OnClick;
public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;

private:
	Vec2 m_scale;
	Texture* m_pBgTex;
	std::wstring m_text;
};
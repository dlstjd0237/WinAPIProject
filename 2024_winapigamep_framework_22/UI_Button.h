#pragma once
#include "Object.h"
#include "Texture.h"
#include <string>;
#include <functional>

class UI_Button : public Object
{
public:
	UI_Button(const std::wstring& bgPath);
	std::function<void()> OnClick;
public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;

private:
	Texture* m_pBgTex;
};
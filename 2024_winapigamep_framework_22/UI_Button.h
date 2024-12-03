#pragma once
#include "Object.h"
#include "Texture.h"
#include <string>;

class UI_Button : public Object
{
public:
	UI_Button(const std::wstring& bgPath);

public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;
	void SetFillAmount(float _amount);

private:
	Texture* m_pBgTex;
};


#pragma once
#include "Object.h";
#include "Texture.h"

class UI_Health : public Object
{
public:
	UI_Health();

public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;
	void SetFillAmount(float _amount);

private:
	float m_fFillAmount;
	Texture* m_pBgTex;
	Texture* m_pFillTex;
};

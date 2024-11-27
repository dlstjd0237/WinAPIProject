#pragma once
#include "Object.h"

class UI_Energy : public Object
{
public:
	UI_Energy();

public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;
	void SetFillAmount(float _amount);

private:
	float m_fFillAmount;
};


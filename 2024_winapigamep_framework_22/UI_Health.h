#pragma once
#include "Object.h";

class UI_Health : public Object
{
public:
	UI_Health();

public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;
private:
	int cnt = 50;
};


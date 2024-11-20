#pragma once
#include "Object.h"

class FillAmount : public Object
{
public:
	FillAmount();

public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;

public:
	float maxAmount = 100;
	float currentAmount = 100;
};


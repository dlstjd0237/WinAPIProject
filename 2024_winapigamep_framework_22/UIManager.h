#pragma once
#include "Object.h"

class UIManager :
	public Object
{
public:
	UIManager();
	~UIManager();

public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;

private:
	int testInt;
};
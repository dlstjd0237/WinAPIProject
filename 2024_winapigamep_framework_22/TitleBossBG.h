#pragma once
#include "Boss.h"

class TitleBossBG : public Boss
{
public:
	TitleBossBG();
	// Boss을(를) 통해 상속됨
	void Render(HDC _hdc) override;
	void PatternInit() override;
};


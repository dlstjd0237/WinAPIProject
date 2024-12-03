#pragma once
#include "Boss.h"
#include "BossPattern.h"

enum class Stage1BossPattern
{
	AllRangeCircleShot,
	OneShot,
	CrossShot,

};

class Stage1Boss : public Boss
{
public:
	Stage1Boss();
public:
	void Render(HDC _hdc) override;
protected:
	void PatternInit() override;
};
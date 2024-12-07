#pragma once
#include "Boss.h"

enum class Stage2BossPattern
{
	RandomLaser,

};
class Stage2Boss : public Boss
{
public:
	Stage2Boss();
public:
	void Render(HDC _hdc) override;
protected:
	void PatternInit() override;
	Texture* _leftTex;

};


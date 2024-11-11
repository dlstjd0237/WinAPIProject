#pragma once
#include "Boss.h"

enum class Stage1BossPattern
{
	CircleShot,
	End
};
class Stage1Boss : public Boss
{
public:
	void PatternInit() override;
};


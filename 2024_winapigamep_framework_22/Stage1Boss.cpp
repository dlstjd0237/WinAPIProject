#include "pch.h"
#include "Stage1Boss.h"
#include "BossPattern.h"
#include "CircleBossPattern.h"
#include "TimeManager.h"
#include "OneShotPattern.h"

Stage1Boss::Stage1Boss()
{
	_patternDelay = 3.f;

	PatternInit();
	PatternIdxInit();
}

void Stage1Boss::PatternInit()
{
	CircleBossPattern* circlePat = new CircleBossPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::CircleShot, circlePat);
	
	OneShotPattern* oneShotPat = new OneShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::OneShot, oneShotPat);

	for (auto iter = _bossPattern.begin(); iter != _bossPattern.end(); iter++)
	{
		iter->second->Init(this);
	}
}

void Stage1Boss::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);
}

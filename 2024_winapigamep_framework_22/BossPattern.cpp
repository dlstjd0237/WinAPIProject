#include "pch.h"
#include "BossPattern.h"

void BossPattern::Init(Boss* boss)
{
	_boss = boss;
}

void BossPattern::Enter()
{
	_isFirst = true;
}

void BossPattern::Update()
{
	if (!_isFirst)
	{
		Enter();
	}
}

void BossPattern::Exit()
{
	_isFirst = false;
	isEnd = false;
}

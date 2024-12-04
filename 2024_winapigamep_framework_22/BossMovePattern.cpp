#include "pch.h"
#include "BossMovePattern.h"
#include "Boss.h"

void BossMovePattern::Init(Boss* boss)
{
	Vec2 size = boss->GetSize();
	float width = SCREEN_WIDTH / 4;

	// ¿ÞÂÊ »ó´Ü
	_positionVec[0] = {size.x, -size.y};

	for (int i = 1; i <= 4; i++)
	{
		_positionVec[i] = { width * i, -size.y };
	}
}

void BossMovePattern::Enter()
{

}

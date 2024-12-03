#pragma once
#include "BossPattern.h"
enum class BossPositionEnum
{
	Left,
	LeftMiddle,
	Middle,
	RightMiddle,
	Right,
	End
};

class BossMovePattern : public BossPattern
{
public:
	void Init(Boss* boss) override;
	void Enter() override;
private:
	vector<Vec2> _positionVec;
	float _delay = 0.25f;
	int _shotCount = 10;
	int _currentShotCount;
	float _elapseTime;
};
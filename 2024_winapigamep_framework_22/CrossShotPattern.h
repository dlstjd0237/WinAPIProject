#pragma once
#include "BossPattern.h"

enum class ShotStyle
{
	defaultShot,
	diagonalShot,
	mixShot,
};

class CrossShotPattern : public BossPattern
{
public:
	CrossShotPattern();
public:
	void Update() override;
	void Exit() override;
	void Enter() override;
private:
	void Shot();
private:
	int _shotCount = 3;
	vector<Vec2> _defaultDirVec;
	vector<Vec2> _diagonalDirVec;
	float _delay = 0.5f;
	int _currentShotCount;
	float _elapseTime;
};


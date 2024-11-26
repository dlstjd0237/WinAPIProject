#pragma once
#include "BossPattern.h"

class OneShotPattern : public BossPattern
{
public:
	void Update() override;
	void SetPattern();
	void Exit() override;
	void Enter() override;
private:
	void Shot();
private:
	float _delay = 0.25f;
	int _shotCount = 10;
	int _currentShotCount;
	float _elapseTime;

	Object* _target;
};


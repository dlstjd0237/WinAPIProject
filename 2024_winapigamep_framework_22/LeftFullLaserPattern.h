#pragma once
#include "BossPattern.h"
#include "WarningPanel.h"
#include "Laser.h"

class LeftFullLaserPattern : public BossPattern
{
public:
	void Update() override;
	void Exit() override;
	void Enter() override;
private:
	void Shot();
private:
	bool _isShotEnd;

	float _shotWaitTime = 1.5f;

	float _elapseTime;
	Vec2 _shootPos;
	WarningPanel* _warningPanel;
	Laser* _laser;
};


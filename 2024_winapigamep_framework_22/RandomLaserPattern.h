#pragma once
#include "BossPattern.h"
#include "WarningPanel.h"

class RandomLaserPattern : public BossPattern
{
public:
	void Update() override;
	void Exit() override;
	void Enter() override;
private:
	void Shot();
private:
	bool _isShotEnd;

	float _shotWaitTime = 1.f;
	int _shotCount = 3;

	float _laserWidth = 5.f;

	float _elapseTime;
	vector<Vec2> _shootPosVec;
	vector<WarningPanel*> _warningPanelVec;
};


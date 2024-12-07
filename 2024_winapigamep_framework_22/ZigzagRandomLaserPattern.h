#pragma once
#include "BossPattern.h"
#include "WarningPanel.h"

class ZigzagRandomLaserPattern : public BossPattern
{
public:
	void Update() override;
	void Exit() override;
	void Enter() override;
private:
	void Ready();
	void Shot();
private:
	bool _isShotStart;
	bool _nextShotWait;

	float _shotWaitTime = 0.75f;
	float _nextWaitTime = 2.f;
	float _laserWidth = 2.f;

	int _shotCount = 3;
	int _currentShotCount = 0;

	int _laserCount = 11;

	float _elapseTime;
	vector<Vec2> _shootPosVec;
	vector<WarningPanel*> _warningPanelVec;
};


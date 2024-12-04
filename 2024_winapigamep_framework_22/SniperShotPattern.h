#pragma once
#include "BossPattern.h"
#include "WarningPanel.h"

class SniperShotPattern : public BossPattern
{
public:
	void Update() override;
	void Exit() override;
	void Enter() override;
private:
	void Sniping();
	void Shot();
private:
	bool _isSniping;
	bool _isShotStart;

	float _shotDelay = 0.15f;
	float _shotWaitTime = 1.f;

	int _shotCount = 3;
	int _currentShotCount = 0;

	int _bulletCount = 3;
	int _currentBulletCount = 0;

	float _elapseTime;
	Vec2 _dir;
	Object* _target;
	WarningPanel* _warningPanel;
};


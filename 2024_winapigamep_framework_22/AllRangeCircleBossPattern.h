#pragma once
#include "BossPattern.h"

class AllRangeCircleBossPattern : public BossPattern
{
private:
	void Shot();
public:
	// BossPattern��(��) ���� ��ӵ�
	void Update() override;
	void Exit() override;
private:
	float _delay = 0.5f;
	int _shotCount = 3;
	int _bulletCount = 15;
	int _currentShotCount;
	float _elapseTime;
};


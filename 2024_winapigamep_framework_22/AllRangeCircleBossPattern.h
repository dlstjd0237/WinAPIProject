#pragma once
#include "BossPattern.h"

class AllRangeCircleBossPattern : public BossPattern
{
private:
	void Shot();
public:
	void Update() override;
	void SetPattern();

	// BossPattern��(��) ���� ��ӵ�
	void Exit() override;
private:
	float _delay = 0.5f;
	int _shotCount = 3;
	int _bulletCount = 25;
	int _currentShotCount;
	float _elapseTime;
};


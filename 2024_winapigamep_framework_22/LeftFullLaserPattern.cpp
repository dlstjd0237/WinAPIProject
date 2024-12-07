#include "pch.h"
#include "LeftFullLaserPattern.h"
#include "Laser.h"

void LeftFullLaserPattern::Update()
{
	BossPattern::Update();

	if(!_isShotEnd)
		Shot();

	if (_isShotEnd && _laser->isEnd)
		isEnd = true;
}

void LeftFullLaserPattern::Exit()
{
	BossPattern::Exit();
	_isShotEnd = false;
}

void LeftFullLaserPattern::Enter()
{
	BossPattern::Enter();

	_shootPos = { SCREEN_WIDTH / 2.f - 100, SCREEN_HEIGHT / 2.f };
	_warningPanel = new WarningPanel(0.1f, _shootPos, { SCREEN_WIDTH / 2 + 500, SCREEN_HEIGHT }, true);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_warningPanel, LAYER::WarningPanel);
}

void LeftFullLaserPattern::Shot()
{
	_elapseTime += fDT;
	if (_elapseTime >= _shotWaitTime)
	{
		_warningPanel->isFade = true;
		_laser = new Laser(1.5f, 3.f, { 3,3 }, 37.f);
		_laser->SetPos(_shootPos);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_laser, LAYER::Laser);

		_isShotEnd = true;
		_elapseTime = 0.f;
	}
}

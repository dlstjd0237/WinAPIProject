#include "pch.h"
#include "RandomLaserPattern.h"
#include "Laser.h"

void RandomLaserPattern::Update()
{
	BossPattern::Update();
	srand((unsigned int)time(NULL));
	Shot();
	if (_isShotEnd)
		isEnd = true;
}

void RandomLaserPattern::Exit()
{
	BossPattern::Exit();
	_warningPanelVec.clear();
	_shootPosVec.clear();
	_isShotEnd = false;
}

void RandomLaserPattern::Enter()
{
	BossPattern::Enter();

	for (int i = 0; i < _shotCount; i++)
	{
		int randPointX = rand() % (SCREEN_WIDTH - 200 + 1) + 100;
		int pointY = SCREEN_HEIGHT / 2;
		Vec2 pos = { randPointX, pointY };
		_shootPosVec.push_back(pos);

		WarningPanel* warningPanel = new WarningPanel(0.1f, pos, { 150, SCREEN_HEIGHT }, true);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(warningPanel, LAYER::WarningPanel);
		_warningPanelVec.push_back(warningPanel);
	}
}

void RandomLaserPattern::Shot()
{
	_elapseTime += fDT;
	if (_elapseTime >= _shotWaitTime)
	{
		for (int i = 0; i < _shotCount; i++)
		{
			_warningPanelVec[i]->isFade = true;
			Laser* laser = new Laser(0.5f, 1.5f, {2,2}, _laserWidth);
			laser->SetPos(_shootPosVec[i]);
			GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(laser, LAYER::Laser);
		}
		_isShotEnd = true;
		_elapseTime = 0.f;
	}
}

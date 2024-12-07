#include "pch.h"
#include "ZigzagRandomLaserPattern.h"
#include "CameraManager.h"
#include "Laser.h"

void ZigzagRandomLaserPattern::Update()
{
	BossPattern::Update();
	srand((unsigned int)time(NULL));
	if (!_isShotStart)
		Ready();
	if (_isShotStart)
		Shot();
	if (_shotCount == _currentShotCount)
		isEnd = true;
}

void ZigzagRandomLaserPattern::Exit()
{
	BossPattern::Exit();
	_warningPanelVec.clear();
	_shootPosVec.clear();
	_isShotStart = false;
	_nextShotWait = false;
}

void ZigzagRandomLaserPattern::Enter()
{
	BossPattern::Enter();
	_currentShotCount = 0;
}

void ZigzagRandomLaserPattern::Ready()
{
	if (_nextShotWait)
	{
		_elapseTime += fDT;
		if (_elapseTime >= _nextWaitTime)
		{
			_elapseTime = 0.f;
			_nextShotWait = false;
		}
		return;
	}

	if (_warningPanelVec.size() == 0)
	{
		int randIdx = rand() % 100;
		float offsetX = _laserWidth * 64.f / 2;
		float startX;
		if (randIdx <= 49)
			startX = offsetX / 2;
		else
			startX = offsetX / 2 + offsetX;

		for (int i = 0; i < _laserCount; i++)
		{
			Vec2 pos = { startX + offsetX * 2 * i, SCREEN_HEIGHT / 2.f };

			WarningPanel* warningPanel = new WarningPanel(0.1f, pos, { _laserWidth * 30.f, (float)SCREEN_HEIGHT }, true);
			GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(warningPanel, LAYER::WarningPanel);
			warningPanel->SetPos(pos);

			_warningPanelVec.push_back(warningPanel);
			_shootPosVec.push_back(pos);
		}
	}

	_elapseTime += fDT;
	if (_shotWaitTime <= _elapseTime)
	{
		_isShotStart = true;
	}
}

void ZigzagRandomLaserPattern::Shot()
{
	GET_SINGLE(CameraManager)->Shake(20, 0.1f);
	for (int i = 0; i < _laserCount; i++)
	{
		_warningPanelVec[i]->isFade = true;
		Laser* laser = new Laser(0.5f, 1.5f, { 2,2 }, _laserWidth);
		laser->SetPos(_shootPosVec[i]);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(laser, LAYER::Laser);
	}

	_elapseTime = 0.f;
	_currentShotCount++;
	_isShotStart = false;
	_nextShotWait = true;
	_warningPanelVec.clear();
	_shootPosVec.clear();
}

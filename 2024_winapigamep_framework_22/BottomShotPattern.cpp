#include "pch.h"
#include "BottomShotPattern.h"
#include "Boss.h"
#include "Projectile.h"

void BottomShotPattern::Update()
{
	BossPattern::Update();
	if (!_isShotStart)
		Sniping();
	if (_isShotStart)
		Shot();
	if (_shotCount == _currentShotCount)
		isEnd = true;
}

void BottomShotPattern::Exit()
{
	BossPattern::Exit();
	_currentBulletCount = 0;
	_currentShotCount = 0;
}

void BottomShotPattern::Enter()
{
	BossPattern::Enter();
	_elapseTime = _shotDelay;
}

void BottomShotPattern::Sniping()
{
	if (_warningPanel == NULL)
	{
		_warningPanel = new WarningPanel(0.1f, {SCREEN_WIDTH / 2.f, SCREEN_HEIGHT - _yAddValue }, {SCREEN_WIDTH, 50}, true);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_warningPanel, LAYER::WarningPanel);
	}

	_elapseTime += fDT;
	if (_shotWaitTime <= _elapseTime)
	{
		_warningPanel->isFade = true;
		_warningPanel = NULL;
		_isShotStart = true;
	}
}

void BottomShotPattern::Shot()
{
	_elapseTime += fDT;
	if (_elapseTime >= _shotDelay)
	{
		if (_bulletCount == _currentBulletCount)
		{
			_currentBulletCount = 0;
			_isShotStart = false;
			_currentShotCount++;
			return;
		}

		Vec2 pos;
		Vec2 dir{ rand() % 2, 0};
		if (dir.x == 0)
			dir.x = -1;
		else
			dir.x = 1;

		if (dir.x == -1)
			pos = { SCREEN_WIDTH - 100.f, (float)SCREEN_HEIGHT - _yAddValue };
		else
			pos = { 100.f, (float)SCREEN_HEIGHT - _yAddValue };

		Projectile* bullet = new Projectile(pos);
		bullet->SetSpeed(1000.f);
		bullet->SetDir(dir);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet, LAYER::PROJECTILE);

		_currentBulletCount++;

		_elapseTime = .0f;
	}
}

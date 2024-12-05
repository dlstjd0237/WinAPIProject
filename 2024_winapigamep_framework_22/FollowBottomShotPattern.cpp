#include "pch.h"
#include "FollowBottomShotPattern.h"
#include "Projectile.h"
#include "Boss.h"

void FollowBottomShotPattern::Update()
{
	BossPattern::Update();
	if (!_isShotStart)
		Sniping();
	if (_isShotStart)
		Shot();
	if (_shotCount == _currentShotCount)
		isEnd = true;
}

void FollowBottomShotPattern::Exit()
{
	BossPattern::Exit();
	_currentBulletCount = 0;
	_currentShotCount = 0;
}

void FollowBottomShotPattern::Enter()
{
	BossPattern::Enter();
	if (_target == NULL)
		_target = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::PLAYER)[0];
	_elapseTime = _shotDelay;
}

void FollowBottomShotPattern::Sniping()
{
	if (_warningPanel == NULL)
	{
		_warningPanel = new WarningPanel(0.1f, { SCREEN_WIDTH / 2.f, _target->GetPos().y }, { SCREEN_WIDTH, 50 }, true);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_warningPanel, LAYER::WarningPanel);
	}

	_elapseTime += fDT;
	_warningPanel->SetPos({ SCREEN_WIDTH / 2.f , _target->GetPos().y });

	if (_shotWaitTime <= _elapseTime)
	{
		_shootPos = _target->GetPos();
		_warningPanel->isFade = true;
		_warningPanel = NULL;
		_isShotStart = true;
	}
}

void FollowBottomShotPattern::Shot()
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

		Vec2 dir{ rand() % 2, 0 };
		if (dir.x == 0)
			dir.x = -1;
		else
			dir.x = 1;

		if (dir.x == -1)
			_shootPos = { SCREEN_WIDTH - 100.f,  _shootPos.y };
		else
			_shootPos = { 100.f, _shootPos.y};

		Projectile* bullet = new Projectile(_shootPos);
		bullet->SetSpeed(1000.f);
		bullet->SetDir(dir);

		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet, LAYER::PROJECTILE);

		_currentBulletCount++;

		_elapseTime = .0f;
	}
}

#include "pch.h"
#include "SniperShotPattern.h"
#include "Boss.h"
#include "Projectile.h"

void SniperShotPattern::Update()
{
	BossPattern::Update();
	if (!_isShotStart)
		Sniping();
	if (_isShotStart)
		Shot();
	if (_shotCount == _currentShotCount)
		isEnd = true;
}

void SniperShotPattern::Exit()
{
	BossPattern::Exit();
	_currentBulletCount = 0;
	_currentShotCount = 0;
}

void SniperShotPattern::Enter()
{
	BossPattern::Enter();
	_elapseTime = _shotDelay;

	if (_target == NULL)
		_target = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::PLAYER)[0];
}

void SniperShotPattern::Sniping()
{
	if (_warningPanel == NULL)
	{
		Vec2 pos = _boss->GetPos();
		_warningPanel = new WarningPanel(0.1f, pos, {SCREEN_WIDTH, 50});
		pos.x = pos.x + SCREEN_WIDTH / 2;
		_warningPanel->SetPos(pos);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_warningPanel, LAYER::WarningPanel);
	}

	Vec2 bossPos = _boss->GetPos();
	Vec2 playerPos = _target->GetPos();
	_dir = playerPos - bossPos;
	_warningPanel->SetRotate(_dir);

	_elapseTime += fDT;
	if (_shotWaitTime <= _elapseTime)
	{
		_warningPanel->isFade = true;
		_warningPanel = NULL;
		_isShotStart = true;
	}
}

void SniperShotPattern::Shot()
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

		Projectile* bullet = new Projectile(_boss->GetPos());
		bullet->SetSpeed(1000.f);
		bullet->SetDir(_dir);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet, LAYER::PROJECTILE);

		_currentBulletCount++;

		_elapseTime = .0f;
	}
}

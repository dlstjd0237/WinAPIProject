#include "pch.h"
#include "FallingShotPattern.h"
#include "Projectile.h"
#include "Boss.h"

void FallingShotPattern::Update()
{
	BossPattern::Update();
	if (!_isShotStart)
		Sniping();
	if (_isShotStart)
		Shot();
	if (_shotCount == _currentShotCount)
		isEnd = true;
}

void FallingShotPattern::Exit()
{
	BossPattern::Exit();
	_currentBulletCount = 0;
	_currentShotCount = 0;
}

void FallingShotPattern::Enter()
{
	BossPattern::Enter();
	if (_target == NULL)
		_target = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::PLAYER)[0];
	_elapseTime = _shotDelay;
}

void FallingShotPattern::Sniping()
{
	if (_warningPanel == NULL)
	{
		_warningPanel = new WarningPanel(0.1f, { _target->GetPos().x, SCREEN_HEIGHT/2.f }, { 50, SCREEN_HEIGHT }, true);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_warningPanel, LAYER::WarningPanel);
	}

	_elapseTime += fDT;
	_warningPanel->SetPos({ _target->GetPos().x, SCREEN_HEIGHT / 2.f });

	if (_shotWaitTime <= _elapseTime)
	{
		_shootPos = _target->GetPos();
		_warningPanel->isFade = true;
		_warningPanel = NULL;
		_isShotStart = true;
	}
}

void FallingShotPattern::Shot()
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

		Projectile* bullet = new Projectile({_shootPos.x, _yAddValue});
		bullet->SetSpeed(1000.f);
		bullet->SetDir({0 , 1});

		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet, LAYER::PROJECTILE);

		_currentBulletCount++;

		_elapseTime = .0f;
	}
}

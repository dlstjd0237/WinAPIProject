#include "pch.h"
#include "CrossTargetShotPattern.h"
#include "Projectile.h"
#include "Boss.h"

void CrossTargetShotPattern::Update()
{
	BossPattern::Update();
	if (!_isShotStart)
		Sniping();
	if (_isShotStart)
		Shot();
	if (_shotCount == _currentShotCount)
		isEnd = true;
}

void CrossTargetShotPattern::Exit()
{
	BossPattern::Exit();
	_currentBulletCount = 0;
	_currentShotCount = 0;
}

void CrossTargetShotPattern::Enter()
{
	BossPattern::Enter();
	if (_target == NULL)
		_target = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::PLAYER)[0];
	_elapseTime = _shotDelay;
}

void CrossTargetShotPattern::Sniping()
{
	if (_verticalWarningPanel == NULL && _horizonWarningPanel == NULL)
	{
		_verticalWarningPanel = new WarningPanel(0.1f, { _target->GetPos().x, SCREEN_HEIGHT / 2.f }, { 50, SCREEN_HEIGHT }, true);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_verticalWarningPanel, LAYER::WarningPanel);

		_horizonWarningPanel = new WarningPanel(0.1f, { SCREEN_WIDTH / 2.f, _target->GetPos().y }, { SCREEN_WIDTH, 50 }, true);
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(_horizonWarningPanel, LAYER::WarningPanel);
	}

	_elapseTime += fDT;
	_verticalWarningPanel->SetPos({ _target->GetPos().x, SCREEN_HEIGHT / 2.f });
	_horizonWarningPanel->SetPos({ SCREEN_WIDTH / 2.f, _target->GetPos().y });

	if (_shotWaitTime <= _elapseTime)
	{
		_shootPos = _target->GetPos();

		_verticalWarningPanel->isFade = true;
		_horizonWarningPanel->isFade = true;

		_verticalWarningPanel = NULL;
		_horizonWarningPanel = NULL;

		_isShotStart = true;
	}
}

void CrossTargetShotPattern::Shot()
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

		Projectile* bullet = new Projectile({ _shootPos.x, _yAddValue });
		bullet->SetSpeed(1000.f);
		bullet->SetDir({ 0 , 1 });
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet, LAYER::PROJECTILE);

		Projectile* bullet1 = new Projectile({ _yAddValue, _shootPos.y });
		bullet1->SetSpeed(1000.f);
		bullet1->SetDir({ 1 , 0 });
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet1, LAYER::PROJECTILE);

		_currentBulletCount++;

		_elapseTime = .0f;
	}
}

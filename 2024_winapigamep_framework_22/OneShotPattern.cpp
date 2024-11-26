#include "pch.h"
#include "OneShotPattern.h"
#include "Projectile.h"
#include "Boss.h"

void OneShotPattern::Update()
{
	BossPattern::Update();
	_elapseTime += fDT;

	if (_elapseTime >= _delay)
	{
		cout << _currentShotCount;
		if (_currentShotCount == _shotCount)
		{
			isEnd = true;
			return;
		}
		Shot();
		_currentShotCount++;
	}
}

void OneShotPattern::SetPattern()
{

}

void OneShotPattern::Exit()
{
	BossPattern::Exit();
	_currentShotCount = 0;
}

void OneShotPattern::Enter()
{
	BossPattern::Enter();
	_elapseTime = _delay;

	if (_target == NULL)
		_target = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::PLAYER)[0];
}

void OneShotPattern::Shot()
{
	Vec2 dir;
	Vec2 bossPos =_boss->GetPos();
	Vec2 playerPos = _target->GetPos();

	dir = playerPos - bossPos;

	Projectile* bullet = new Projectile;

	bullet->SetPos(_boss->GetPos());
	bullet->SetDir(dir);

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet, LAYER::PROJECTILE);
	_elapseTime = .0f;
}

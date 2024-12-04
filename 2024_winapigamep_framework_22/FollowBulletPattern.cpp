#include "pch.h"
#include "Boss.h"
#include "FollowBulletPattern.h"

void FollowBulletPattern::Update()
{
	BossPattern::Update();

	if(!_isShootReady)
		Ready();
	if (_isShootReady && !_isAllBulletShoot)
		Shot();
	if (_isShootStart)
		FollowTarget();
	if (_isAllBulletShoot)
		DestroyCheck();
}

void FollowBulletPattern::Exit()
{
	BossPattern::Exit();
	_currentBulletCount = 0;

	_isShootStart = false;
	_isShootReady = false;
	_isAllBulletShoot = false;
}

void FollowBulletPattern::Enter()
{
	BossPattern::Enter();
	_elapseTime = _shotDelay;

	if (_target == NULL)
		_target = GET_SINGLE(SceneManager)->GetCurrentScene()->GetLayerObjects(LAYER::PLAYER)[0];
}

void FollowBulletPattern::Shot()
{
	_elapseTime += fDT;
	if (_elapseTime >= _shotDelay)
	{
		if (_defaultBulletCount == _currentBulletCount)
		{
			_isAllBulletShoot = true;
			return;
		}

		if (_currentBulletCount == 1)
			_isShootStart = true;

		_bulletVec[_currentBulletCount]->SetSpeed(300.f);
		_currentBulletCount++;
	}
}

void FollowBulletPattern::Ready()
{
	_elapseTime += fDT;
	if (_elapseTime >= _readyDelay)
	{
		if (_defaultBulletCount == _currentBulletCount)
		{
			_isShootReady = true;
			_currentBulletCount = 0;
			_elapseTime = .0f;
			return;
		}

		float x = cosf(rand() % 360 * PI / 180);
		float y = sinf(rand() % 360 * PI / 180);

		Vec2 dir = { x,y };
		dir.Normalize();

		Vec2 pos = _boss->GetPos();
		pos += dir * _readyRadius;

		Projectile* bullet = new Projectile(pos);
		bullet->SetSpeed(.0f);
		_bulletVec.push_back(bullet);

		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet, LAYER::PROJECTILE);
		_currentBulletCount++;
		_elapseTime = .0f;
	}
}

void FollowBulletPattern::FollowTarget()
{
	for (int i = 0; i < _defaultBulletCount; i++)
	{
		Vec2 dir;
		Vec2 pos = _bulletVec[i]->GetPos();
		Vec2 playerPos = _target->GetPos();

		dir = playerPos - pos;
		_bulletVec[i]->SetDir(dir);
	}
}

void FollowBulletPattern::DestroyCheck()
{
	_elapseTime += fDT;
	if (_elapseTime >= _bulletLifeTime)
	{
		for (int i = 0; i < _defaultBulletCount; i++)
		{
			_bulletVec[i]->DestroyAction();
		}
		isEnd = true;
	}
}

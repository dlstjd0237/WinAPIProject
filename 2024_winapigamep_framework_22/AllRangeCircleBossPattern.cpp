#include "pch.h"
#include "Projectile.h"
#include "AllRangeCircleBossPattern.h"
#include "Boss.h"

void AllRangeCircleBossPattern::Update()
{
	BossPattern::Update();
	_elapseTime += fDT;

	if (_elapseTime >= _delay)
	{
		if (_currentShotCount == _shotCount)
		{
			isEnd = true;
			return;
		}
		Shot();
		_currentShotCount++;
	}
}

void AllRangeCircleBossPattern::Shot()
{
	for (int i = 0; i < _bulletCount; i++)
	{
		float angle = 360.f / _bulletCount * i;
		float x = cosf(angle * PI / 180);
		float y = sinf(angle * PI / 180);
		
		Vec2 dir = { x,y };
		Vec2 pos = _boss->GetPos();
		pos += dir * 80; 

		Projectile* pProj = new Projectile(pos);
		pProj->SetDir(dir);

		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
	}
	_elapseTime = .0f;
}

void AllRangeCircleBossPattern::Exit()
{
	BossPattern::Exit();
	_currentShotCount = 0;
	_elapseTime = _delay;
}



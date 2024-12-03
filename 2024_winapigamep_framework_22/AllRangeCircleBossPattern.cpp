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
		Projectile* pProj = new Projectile;
		
		pProj->SetPos(_boss->GetPos());

		float angle = 360.f / _bulletCount * i;
		float x = cosf(angle * PI / 180);
		float y = sinf(angle * PI / 180);

		pProj->SetDir({ x,y });
		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
	}
	_elapseTime = .0f;
}

void AllRangeCircleBossPattern::SetPattern()
{

}

void AllRangeCircleBossPattern::Exit()
{
	BossPattern::Exit();
	_currentShotCount = 0;
	_elapseTime = _delay;
}



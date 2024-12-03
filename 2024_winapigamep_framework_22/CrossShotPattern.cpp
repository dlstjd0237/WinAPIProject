#include "pch.h"
#include "CrossShotPattern.h"
#include "Projectile.h"
#include "Boss.h"

CrossShotPattern::CrossShotPattern()
{
	_defaultDirVec.push_back({ 1, 0 });
	_defaultDirVec.push_back({ -1, 0 });
	_defaultDirVec.push_back({ 0, 1 });
	_defaultDirVec.push_back({ 0,-1 });

	_diagonalDirVec.push_back({ 1, 1 });
	_diagonalDirVec.push_back({ 1, -1 });
	_diagonalDirVec.push_back({ -1, -1 });
	_diagonalDirVec.push_back({ -1, 1 });
}

void CrossShotPattern::Update()
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

void CrossShotPattern::Exit()
{
	BossPattern::Exit();
	_currentShotCount = 0;
}

void CrossShotPattern::Enter()
{
	BossPattern::Enter();
	_elapseTime = _delay;
}

void CrossShotPattern::Shot()
{
	ShotStyle randShot = (ShotStyle)(rand() % 3);
	vector<Vec2> currentDirs;

	switch (randShot)
	{
	case ShotStyle::defaultShot:
		currentDirs = _defaultDirVec;
		break;
	case ShotStyle::diagonalShot:
		currentDirs = _diagonalDirVec;
		break;
	case ShotStyle::mixShot:
		currentDirs = _defaultDirVec;
		for (int i = 0; i < 4; i++)
			currentDirs.push_back(_diagonalDirVec[i]);
		break;
	}

	for (int i = 0; i < currentDirs.size(); i++)
	{
		Vec2 dir = currentDirs[i];
		Vec2 pos = _boss->GetPos();
		pos += dir * 80;

		Projectile* bullet = new Projectile(pos);
		bullet->SetDir(dir);

		GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(bullet, LAYER::PROJECTILE);
	}

	_elapseTime = .0f;
}

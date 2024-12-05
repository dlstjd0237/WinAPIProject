#pragma once
#include "BossPattern.h"
#include "Projectile.h"

class FollowBulletPattern : public BossPattern
{
public:
	void Update() override;
	void Exit() override;
	void Enter() override;
private:
	void Shot();
	void Ready();
	void FollowTarget();
	void DestroyCheck();
private:
	vector<Projectile*> _bulletVec;
	bool _isShootReady;
	bool _isAllBulletShoot;
	bool _isShootStart;
	float _readyDelay = 0.25f;
	float _readyRadius = 100.f;

	int _defaultBulletCount = 3;
	int _currentBulletCount;
	float _shotDelay = 0.25f;
	float _bulletLifeTime = 5.f;

	float _elapseTime;
	Object* _target;
};


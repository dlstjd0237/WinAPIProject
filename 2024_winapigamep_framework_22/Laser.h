#pragma once
#include "Object.h"

class Texture;
enum class LaserStateType 
{
	Ready,
	Fire,
	Firing,
	End
};

class Laser : public Object
{
public:
	Laser(float _waitTime, float _fireTime, Vec2 readyScale, float laserWidth);
private:
	void Update() override;
	void Render(HDC _hdc) override;
	void DestroyAction();
	bool AnimationEndCheck();

	void Ready();
	void Fire();
	void EndCheck();
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	float _waitTime;
	float _fireTime;
	float _deltaTime;
	float _damageDelay = 1.f;
	float _damageDelta = _damageDelay;

	Vec2 _animScale;
	Vec2 _laserScale;
	Texture* _m_pTex;

	bool _isReady = true;
	bool _isFiring;
	bool _isEnd;
	LaserStateType _currentType = LaserStateType::Ready;
};


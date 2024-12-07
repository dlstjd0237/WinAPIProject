#include "pch.h"
#include "Laser.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "EntityManager.h"
#include "Animator.h"
#include "Animation.h"
#include "Collider.h"
#include "Player.h"

Laser::Laser(float waitTime, float fireTime, Vec2 readyScale, float laserWidth)
{
	_waitTime = waitTime;
	_fireTime = fireTime;

	_m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"BossLaser", L"Texture\\Effect\\BossEffect.bmp");
	AddComponent<Animator>();
	AddComponent<Collider>();

	float sliceWidth = 64.f;
	float sliceHeight = 64.f;

	_animScale = readyScale;
	_laserScale = { laserWidth, 12.f };
	_colliderScale = { _laserScale.x * 64.f / 2, _laserScale.y * 64.f };

	GetComponent<Animator>()->CreateAnimation(L"Ready", _m_pTex, Vec2(0.f, sliceHeight * 27),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 9, 0.05f, false, _animScale);
	GetComponent<Animator>()->CreateAnimation(L"Fire", _m_pTex, Vec2(0.f, sliceHeight * 20),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 2, 0.1f, false, _laserScale);
	GetComponent<Animator>()->CreateAnimation(L"Firing", _m_pTex, Vec2(sliceWidth * 2, sliceHeight * 20),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 4, 0.1f, false, _laserScale);
	GetComponent<Animator>()->CreateAnimation(L"End", _m_pTex, Vec2(sliceWidth * 6, sliceHeight * 20),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 2, 0.1f, false, _laserScale);

	GetComponent<Animator>()->PlayAnimation(L"Ready", true);
}

void Laser::Update()
{
	if (_isReady)
		Ready();
	if (_isFiring)
		Fire();
	if (isEnd)
		EndCheck();
}

void Laser::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Laser::DestroyAction()
{
	GET_SINGLE(EventManager)->DeleteObject(this);
}

bool Laser::AnimationEndCheck()
{
	if (GetComponent<Animator>()->GetCurrentAnim()->GetCurFrame() == GetComponent<Animator>()->GetCurrentAnim()->GetMaxFrame() - 1)
			return true;

	return false;
}

void Laser::Ready()
{
	_deltaTime += fDT;
	if (_deltaTime >= _waitTime)
	{
		GetComponent<Animator>()->PlayAnimation(L"Fire", false);
		_currentType = LaserStateType::Fire;
		_isReady = false;
		_isFiring = true;
		_deltaTime = 0;
	}
}

void Laser::Fire()
{
	if (_currentType == LaserStateType::Fire && AnimationEndCheck())
	{
		GetComponent<Animator>()->PlayAnimation(L"Firing", true);
		GetComponent<Collider>()->SetSize(_colliderScale);
		_currentType = LaserStateType::Firing;
	}

	_deltaTime += fDT;
	if (_deltaTime >= _fireTime)
	{
		_isFiring = false;
		isEnd = true;
		GetComponent<Collider>()->SetSize({0 , 0});
		GetComponent<Animator>()->PlayAnimation(L"End", false);
		_currentType = LaserStateType::End;
	}
}

void Laser::EndCheck()
{
	if (_currentType == LaserStateType::End && AnimationEndCheck())
		DestroyAction();
}

void Laser::EnterCollision(Collider* _other)
{
}

void Laser::StayCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();

	if (_damageDelta <= _damageDelay)
	{
		_damageDelta += fDT;
	}

	if (pOtherObj->GetName() == L"Player")
	{
		if (_damageDelta >= _damageDelay)
		{
			GET_SINGLE(EntityManager)->GetPlayer()->OnDamaged(1.f);
			_damageDelta = 0;
		}
	}
}

void Laser::ExitCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();

	if (pOtherObj->GetName() == L"Player")
	{
		_damageDelta = _damageDelay;
	}
}

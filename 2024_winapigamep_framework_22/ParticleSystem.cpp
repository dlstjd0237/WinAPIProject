#include "pch.h"
#include "ParticleSystem.h"
#include "TimeManager.h"
#include "EventManager.h"

ParticleSystem::ParticleSystem(ParticleType type, float duration, float scale, bool isLoop)
{
	AddComponent<Animator>();
	ParticleInit(type);

	_duration = duration;
	_duration *= count;

	GetComponent<Animator>()->CreateAnimation(L"Effect", _m_pTex, leftTop,
		size, step, count, duration, false, scale, offset);
	GetComponent<Animator>()->PlayAnimation(L"Effect", isLoop);
}

void ParticleSystem::Update()
{
	_deltaTime += fDT;
	if (_duration <= _deltaTime)
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void ParticleSystem::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void ParticleSystem::ParticleInit(ParticleType type)
{
	switch (type)
	{
	case ParticleType::BulletShot:
		_m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"BulletShot", L"Texture\\Effect\\BulletParticle.bmp");
		leftTop = { 0.f , 64.f * 13};
		size = { 64.f ,64.f };
		step = { 64.f , 0.f };
		count = 4;
		break;
	case ParticleType::BulletDestroy:
		_m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"BulletDestroy", L"Texture\\Effect\\BulletParticle.bmp");
		leftTop = { 64.f * 5, 64.f * 10 };
		size = { 64.f ,64.f };
		step = { 64.f , 0.f };
		count = 5;
		break;
	}
}

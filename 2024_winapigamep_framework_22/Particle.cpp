#include "pch.h"
#include "Particle.h"
#include "TimeManager.h"
#include "EventManager.h"

Particle::Particle(ParticleType type, float duration, float scale, bool isLoop)
{
	AddComponent<Animator>();
	ParticleInit(type);
	_duration = duration;

	GetComponent<Animator>()->CreateAnimation(L"Effect", _m_pTex, leftTop,
		size, step, count, duration, false, scale, offset);
	GetComponent<Animator>()->PlayAnimation(L"Effect", isLoop);
}

void Particle::Update()
{
	_deltaTime += fDT;
	if (_duration + 0.1f <= _deltaTime)
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void Particle::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Particle::ParticleInit(ParticleType type)
{
	switch (type)
	{
	case ParticleType::BulletShot:
		_m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"BulletShot", L"Texture\\Effect\\BulletParticle.bmp");
		leftTop = { 0.f , 64.f * 6 };
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

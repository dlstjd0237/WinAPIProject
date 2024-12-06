#include "pch.h"
#include "Projectile.h"
#include "TimeManager.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Particle.h"
#include "EventManager.h"
#include "SceneManager.h"
#include "Scene.h"

Projectile::Projectile(Vec2 pos)
{
	SetPos(pos);

	Particle* particle = new Particle(ParticleType::BulletShot, 0.075f, 1.f, false);
	particle->SetPos(pos);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(particle, LAYER::Effect);

	SetName(L"Projectile");

	AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 30.f, 30.f});

	_m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Bullet", L"Texture\\Projectile.bmp");
	AddComponent<Animator>();
	GetComponent<Animator>()->CreateAnimation(L"Play", _m_pTex, Vec2(24.f * 16, 24.f * 12),
		Vec2(24.f, 24.f), Vec2(24.f, 0.f), 8, 0.1f, false, _animScale);
	GetComponent<Animator>()->PlayAnimation(L"Play", true);
}

Projectile::~Projectile()
{
}

void Projectile::Update()
{
	Vec2 vPos = GetPos();
	vPos.x += m_vDir.x * _speed * fDT;
	vPos.y += m_vDir.y * _speed * fDT;
	SetPos(vPos);

	if (vPos.y < 0 || vPos.y > SCREEN_HEIGHT || vPos.x < 0 || vPos.x > SCREEN_WIDTH)
	{
		DestroyAction();
	}
}

void Projectile::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Projectile::DestroyAction()
{
	Particle* particle = new Particle(ParticleType::BulletDestroy, 0.05f, 1.f, false);
	particle->SetPos(GetPos());
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(particle, LAYER::Effect);
	GET_SINGLE(EventManager)->DeleteObject(this);
}

void Projectile::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Player")
	{
		DestroyAction();
	}
	if (pOtherObj->GetName() == L"Ground")
	{
		DestroyAction();
	}
}

void Projectile::StayCollision(Collider* _other)
{
}

void Projectile::ExitCollision(Collider* _other)
{
}

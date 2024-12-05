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
	: m_angle(0.f)
	, m_vDir(1.f, 1.f)
{
	SetPos(pos);

	Particle* particle = new Particle(ParticleType::BulletShot, 0.075f, 1.f, false);
	particle->SetPos(pos);
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(particle, LAYER::Effect);

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Bullet", L"Texture\\Bullet.bmp");
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 20.f,20.f });
	SetName(L"Projectile");
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
	Vec2 vSize = GetSize();

	if (vPos.y < 0 || vPos.y > SCREEN_HEIGHT || vPos.x < 0 || vPos.x > SCREEN_WIDTH)
	{
		DestroyAction();
	}
}

void Projectile::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0, width, height, RGB(255, 0, 255));
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

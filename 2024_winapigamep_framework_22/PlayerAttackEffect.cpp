#include "pch.h"
#include "PlayerAttackEffect.h"
#include "Collider.h"
#include "TimeManager.h"
#include "EventManager.h"

PlayerAttackEffect::PlayerAttackEffect()
{
	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 150,150 });
}

PlayerAttackEffect::~PlayerAttackEffect()
{
}

void PlayerAttackEffect::Update()
{

	m_attackTimer += fDT;
	if (m_attackTimer >= m_attackDelay)
	{
		GET_SINGLE(EventManager)->DeleteObject(this);
	}

}

void PlayerAttackEffect::Render(HDC _hdc)
{
	ComponentRender(_hdc);

}

void PlayerAttackEffect::EnterCollistion(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Boss") {

	}
}

void PlayerAttackEffect::StayCollistion(Collider* _other)
{
}

void PlayerAttackEffect::ExitCollistion(Collider* _other)
{
}

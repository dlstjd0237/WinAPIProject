#include "pch.h"
#include "PlayerAttackEffect.h"
#include "Collider.h"
#include "TimeManager.h"
#include "EventManager.h"

PlayerAttackEffect::PlayerAttackEffect(Object* obj, bool _flip)
{
	SetOwner(obj);
	SetFlip(_flip);
	SetOffSet({ 80,0 });

	this->AddComponent<Collider>();
	GetComponent<Collider>()->SetSize({ 150,150 });
}

PlayerAttackEffect::~PlayerAttackEffect()
{
}

void PlayerAttackEffect::Update()
{
	Vec2 pPos = GetOwner()->GetPos();

	if (GetFlip() == true)
		pPos += GetOffset();
	else
		pPos -= GetOffset();


	this->SetPos({ pPos.x,pPos.y });
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
	cout << "오브젝트 공격";

	if (pOtherObj->GetName() == L"Enemy") {
		cout << "적 공격";
	}
}

void PlayerAttackEffect::StayCollistion(Collider* _other)
{
}

void PlayerAttackEffect::ExitCollistion(Collider* _other)
{
}

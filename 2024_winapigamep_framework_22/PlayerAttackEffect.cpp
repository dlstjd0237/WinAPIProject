#include "pch.h"
#include "PlayerAttackEffect.h"
#include "Collider.h"
#include "TimeManager.h"
#include "EventManager.h"
#include "CollisionManager.h"

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
	//m_attackTimer += fDT;
	//if (m_attackTimer >= m_attackDelay)
	//{
	//	GET_SINGLE(EventManager)->DeleteObject(this);
	//}
}

void PlayerAttackEffect::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void PlayerAttackEffect::EnterCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	cout << "������Ʈ ����";

	if (pOtherObj->GetName() == L"Enemy") {
		cout << "�� ����";
		GET_SINGLE(EventManager)->DeleteObject(this);
	}
}

void PlayerAttackEffect::StayCollision(Collider* _other)
{
	cout << "�� ����";

}

void PlayerAttackEffect::ExitCollision(Collider* _other)
{
	cout << "�� ����";

}

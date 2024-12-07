#include "pch.h"
#include "Object.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Component.h"
Object::Object()
	: m_vPos{}
	, m_vSize{}
	, m_IsDie(false)
{
}

Object::~Object()
{
	for (Component* com : m_vecComponents)
	{
		if (com != nullptr)
			delete com;
	}
	m_vecComponents.clear();
}

void Object::LateUpdate()
{
	for (Component* com : m_vecComponents)
	{
		if (com)
		{
			com->LateUpdate();
		}
	}
}

void Object::ComponentRender(HDC _hdc)
{
	for (Component* com : m_vecComponents)
	{
		if (com)
		{
			com->Render(_hdc);
		}
	}
}

void Object::EnterCollision(Collider* _other)
{

}

void Object::StayCollision(Collider* _other)
{
}

void Object::ExitCollision(Collider* _other)
{
}


void Object::UseGravity()
{
	if (m_IsUseGravity == false) {
		m_vGravity = 0;
		return;
	}
	// 중력 가속도 누적
	m_vGravity += m_gravity * fDT; // 중력에 의한 변화 누적

	// 새로운 위치 계산
	Vec2 newPos = { m_vPos.x, m_vPos.y + m_vGravity };

	// 위치 설정
	SetPos(newPos);
}

void Object::DeadProcess()
{

}

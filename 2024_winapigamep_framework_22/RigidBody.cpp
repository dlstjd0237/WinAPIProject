#include "pch.h"
#include "RigidBody.h"
#include "TimeManager.h"
#include "Object.h"

RigidBody::RigidBody()
	:
	m_fMass(1)
{
}

RigidBody::~RigidBody()
{
}

void RigidBody::LateUpdate()
{
	// 힘의 크기
	float fForce = m_vForce.Length();

	if (0.f != fForce) {
		// 힘의 방향
		m_vForce.Normalize();

		//가속도의 크기
		float m_fAccel = fForce / m_fMass;

		//가속도
		m_vAccel = m_vForce / m_fMass;

		//속도
		m_vVelocity += m_vAccel;

		// 속도에 따른 이동
		Move();


	}
	// 힘 초기화
	m_vForce = Vec2(0.f, 0.f);

}

void RigidBody::Render(HDC _hdc)
{
}

void RigidBody::finalupdate()
{

}
void RigidBody::Move()
{
	// 이동 속력
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed && m_pOwner != __nullptr) {

		cout << "이동중";
		//이동 방향
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}


}

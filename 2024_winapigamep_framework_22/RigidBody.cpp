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
	// ���� ũ��
	float fForce = m_vForce.Length();

	if (0.f != fForce) {
		// ���� ����
		m_vForce.Normalize();

		//���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		//���ӵ�
		m_vAccel = m_vForce / m_fMass;

		//�ӵ�
		m_vVelocity += m_vAccel;

		// �ӵ��� ���� �̵�
		Move();


	}
	// �� �ʱ�ȭ
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
	// �̵� �ӷ�
	float fSpeed = m_vVelocity.Length();

	if (0.f != fSpeed && m_pOwner != __nullptr) {

		cout << "�̵���";
		//�̵� ����
		Vec2 vDir = m_vVelocity;
		vDir.Normalize();

		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}


}

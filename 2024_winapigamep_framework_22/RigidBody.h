#pragma once
#include "Component.h"

class Object;

class RigidBody :public Component
{
private:
	Object* m_pOwner;

	Vec2 m_vForce; //ũ�� ����
	Vec2 m_vAccel; //���ӵ�
	Vec2 m_vVelocity; //�ӵ�
	float m_fMass; //����

public:
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void finalupdate();

public:
	void AddForce(Vec2 _vF) {  m_vForce += _vF; }

	void SetMass(float _fMass) { m_fMass = _fMass; }

	float GetMass() { return m_fMass; }
private:
	void Move();

public:
	RigidBody();
	~RigidBody();

	friend class Object;
};


#pragma once
#include "Component.h"

class Object;

class RigidBody :public Component
{
private:
	Object* m_pOwner;

	Vec2 m_vForce; //크기 방향
	Vec2 m_vAccel; //가속도
	Vec2 m_vVelocity; //속도
	float m_fMass; //질량

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


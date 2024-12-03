#pragma once
#include "Object.h"
class PlayerAttackEffect :
	public Object
{
public:
	PlayerAttackEffect();
	~PlayerAttackEffect();

public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollistion(Collider* _other);
	virtual void StayCollistion(Collider* _other);
	virtual void ExitCollistion(Collider* _other);
private:
	float m_damage = 5.0f;
	float m_attackTimer = 0.f;
	float m_attackDelay = 0.6f;
};


#pragma once
#include "Object.h"
class PlayerAttackEffect :
	public Object
{
public:
	PlayerAttackEffect(Object* obj, bool _flip);
	~PlayerAttackEffect();

public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	float m_damage = 5.0f;
	float m_attackTimer = 0.f;
	float m_attackDelay = 0.6f;

private:
	Object* m_player;
	Vec2 m_offSet;
	bool m_flip = false;
public:
	void SetOwner(Object* _obj) { m_player = _obj; }
	void SetOffSet(Vec2 _v) { m_offSet = _v; }
	void SetFlip(bool _flip) { m_flip = _flip; }

	const Object* GetOwner() const { return m_player; }
	const Vec2 GetOffset() const { return m_offSet; }
	const bool GetFlip() const { return m_flip; }
};


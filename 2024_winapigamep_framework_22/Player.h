#pragma once
#include "Object.h"
class Texture;

class Player : public Object
{
public:
	Player();
	~Player();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	void CreateProjectile();
	void CreateAttackEffect();
	void Jump();

private:
	Texture* m_pTex;
	float m_speed;
	float m_energy = 1.0f;
	float m_jumpVelocity = 0.f;
	float m_attackTimer = 0.f;
	float m_attackDelay = 0.4f;

	bool m_isFlip = false;

	bool m_isGround = false;

	bool m_isJumping = false;

	bool m_isMoveing = false;

	bool m_isAttackTrigger = false;

	map<PLAYER_ANIM_TYPE, bool> m_actionMap;
private:
	float GetEnergy() { return m_energy; }
	void SetEnergy(float value)
	{
		m_energy = min(value, MAXENERGY);
	}
	void AnimationChange(PLAYER_ANIM_TYPE animType, bool Flip = false);
	void ActionMapChange(PLAYER_ANIM_TYPE animType)
	{
		for (auto& m : m_actionMap)
		{
			m.second = false;
		}
		m_actionMap[animType] = true;
	}

	void PerformAttack();
};


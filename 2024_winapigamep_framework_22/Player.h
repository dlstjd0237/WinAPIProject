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
	void Jump();

private:
	Texture* m_pTex;
	float m_speed;
	float m_energy = 1.0f;
	float m_jumpVelocity = 0.f;
	bool m_isJumping = false;
	bool m_isMoveing = false;

private:
	float GetEnergy() { return m_energy; }
	void SetEnergy(float value)
	{
		m_energy = min(value, MAXENERGY);
	}
	void AnimationChange(PLAYER_ANIM_TYPE animType, bool Flip = false);

};


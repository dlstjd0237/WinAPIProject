#pragma once
#include "Object.h"
#include "HealthSystem.h"
class Texture;

class Player : public Object
{
public:
	Player(UI_Health* bar);
	~Player();
public:
	void Update() override;
	void LateUpdate() override;
	void Render(HDC _hdc) override;
	void DeadProcess() override;

public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	void CreateAttackEffect();
	void Jump();

private:
	Texture* m_pTex;
	Vec2 m_playerScale = { 2,2 };
	float m_speed = 10.f;
	float m_energy = 1.0f;
	float m_jumpVelocity = 0.f;
	float m_attackTimer = 0.f;
	float m_attackDelay = 0.4f;

	bool m_isFlip = false;

	bool m_isGround = false;

	bool m_isJumping = false;

	bool m_isMoveing = false;

	bool m_isAttackTrigger = false;

	bool m_isLeftWallDetected = false;
	bool m_isRightWallDetected = false;

	map<PLAYER_ANIM_TYPE, bool> m_actionMap;
	HealthSystem* health;
public:
	const float GetEnergy() const { return m_energy; }
	const Vec2	GetPlayerScale() const { return m_playerScale; }
	const bool GetWallDetected()const { return m_isLeftWallDetected == true || m_isRightWallDetected; }

	void SetEnergy(float value) { m_energy = min(value, MAXENERGY); }
	void SetPlayerScale(Vec2 _scale) { m_playerScale = _scale; }

	void AnimationChange(PLAYER_ANIM_TYPE animType, bool Flip = false);
	void ActionMapChange(PLAYER_ANIM_TYPE animType)
	{
		for (auto& m : m_actionMap)
		{
			m.second = false;
		}
		m_actionMap[animType] = true;
	}
	void OnDamaged(float damage);
	void PerformAttack();
};


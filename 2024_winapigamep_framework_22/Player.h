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
public :
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	void CreateProjectile();
	void Jump();
	Texture* m_pTex;
	float m_speed;

private:
	bool m_isJumping = false;
	float m_jumpVelocity = 0.f;

};


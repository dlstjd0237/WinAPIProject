#pragma once
#include "Object.h"
class Texture;
class Projectile : public Object
{
public:
	Projectile(Vec2 pos);
	~Projectile();
	void Update() override;
	void Render(HDC _hdc) override;
	void DestroyAction();
public:
	void SetAngle(float _f)
	{
		m_angle = _f;
	}
	void SetDir(Vec2 _dir)
	{
		m_vDir = _dir;
		m_vDir.Normalize();
	}
	void SetSpeed(float speed)
	{
		_speed = speed;
	}
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	//float m_dir;
	float _dt;
	float _speed = 500.f;
	float m_angle;
	Vec2 m_vDir;
	Texture* m_pTex;
};


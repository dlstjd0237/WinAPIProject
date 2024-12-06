#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Animator.h"

enum class ParticleType 
{
	BulletShot,
	BulletDestroy,
};


class ParticleSystem : public Object
{
public:
	ParticleSystem(ParticleType type, float duration, float scale, bool isLoop);
public:
	void Update() override;
	void Render(HDC _hdc) override;
private:
	void ParticleInit(ParticleType type);
protected:
	Texture* _m_pTex;
private:
	float _deltaTime;
	float _duration;
	Vec2 leftTop, size, step, offset;
	UINT count = 1;
};


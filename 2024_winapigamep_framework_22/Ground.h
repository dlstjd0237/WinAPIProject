#pragma once
#include "Object.h"

class Texture;
class Ground :
	public Object
{
public:
	Ground(bool _useTextur, Vec2 _colliderSize, Vec2 _colliderOffSet);
	~Ground();
public:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
private:
	Texture* m_pTex;
	bool m_useTexur = false;
};


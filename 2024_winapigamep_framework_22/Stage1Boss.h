#pragma once
#include "Boss.h"
#include "BossPattern.h"

enum class Stage1BossPattern
{
	AllRangeCircleShot,
	OneShot,
	CrossShot,
	FollowShot,
	SniperShot,
};

class Stage1Boss : public Boss
{
public:
	Stage1Boss();
	void EnterCollision(Collider* _other) override
	{
		cout << 3132132132 << endl;
	}
public:
	void Render(HDC _hdc) override;
protected:
	void PatternInit() override;

};
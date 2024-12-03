#pragma once
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"

class Boss;
class BossPattern
{
public:
	void Init(Boss* boss);
	virtual void Enter();
	virtual void Update();
	virtual void Exit();
private:
	bool _isFirst;
protected:
	Boss* _boss;
public:
	bool canUse = true;
	bool isEnd;
	bool isArrived;
};


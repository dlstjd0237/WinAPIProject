#pragma once
#include "Scene.h"

class BossTestScene : public Scene
{
	// Scene을(를) 통해 상속됨
	void Init() override;
	virtual void Update() override;
};


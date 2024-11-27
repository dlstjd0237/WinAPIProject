#pragma once
#include "Scene.h"
#include "UI_Health.h"
class BossTestScene : public Scene
{
	void Init() override;
	virtual void Update() override;

	UI_Health* pUIHealth = new UI_Health;
};
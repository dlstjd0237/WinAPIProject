#pragma once
#include "Scene.h"
#include "UI_Health.h"
#include "UI_Button.h"

class Stage1BossScene : public Scene
{
	void Init() override;
	virtual void Update() override;

	Object* pPlayerHealth = new UI_Health(L"Texture\\plane.bmp", L"Texture\\planem.bmp");
	Object* pBossHealth = new UI_Health(L"Texture\\plane.bmp", L"Texture\\planem.bmp");
	Object* pPlayerEnergy = new UI_Health(L"Texture\\plane.bmp", L"Texture\\planem.bmp");
};
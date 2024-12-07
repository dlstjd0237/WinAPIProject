#pragma once
#include "Scene.h"
#include "UI_Health.h"
#include "UI_Button.h"

class Stage1BossScene : public Scene
{
	void Init() override;
	virtual void Update() override;
	void Release() override;
public:
	UI_Health* pPlayerHealth = new UI_Health(L"Texture\\PlayerEmptyAmount.bmp", L"Texture\\PlayerFullHealth.bmp");
	UI_Health* pBossHealth = new UI_Health(L"Texture\\BossEmpty.bmp", L"Texture\\BossAmount.bmp");
	UI_Health* pPlayerEnergy = new UI_Health(L"Texture\\PlayerEmptyAmount.bmp", L"Texture\\EnergyAmount.bmp");
};
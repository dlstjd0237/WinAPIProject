#pragma once
#include "Scene.h"
#include "UI_Health.h"
#include "UI_Button.h"

class BossTestScene : public Scene
{
	void Init() override;
	virtual void Update() override;

	UI_Health* pPlayerHealth = new UI_Health(L"Texture\\PlayerEmptyAmount.bmp", L"Texture\\PlayerFullHealth.bmp",
		L"PlayerEmptyAmount", L"PlayerFullHealth", { 3.3f, 2.5f });
	UI_Health* pBossHealth = new UI_Health(L"Texture\\BossEmpty.bmp", L"Texture\\BossAmount.bmp", 
		L"BossEmpty", L"BossAmount", {3.3f, 3.3f});
	UI_Health* pPlayerEnergy = new UI_Health(L"Texture\\PlayerEmptyAmount.bmp", L"Texture\\EnergyAmount.bmp",
		L"PlayerEmptyAmount", L"EnergyAmount", {3.3f, 2.5f });
};
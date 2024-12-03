#pragma once
#include "Scene.h"
#include "UI_Health.h"
#include "UI_Button.h"

class BossTestScene : public Scene
{
	void Init() override;
	virtual void Update() override;

	UI_Health* pUIHealth = new UI_Health(L"Texture\\plane.bmp", L"Texture\\planem.bmp");
	UI_Button* pUIButton = new UI_Button(L"Texture\\planem.bmp");
};
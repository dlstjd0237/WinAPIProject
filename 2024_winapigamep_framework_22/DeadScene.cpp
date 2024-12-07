#include "pch.h"
#include "DeadScene.h"
#include "UI_Button.h"
#include "SceneManager.h"
#include "Background.h"
#include "BackgroundAnimation.h"
#include "ResourceManager.h"

void DeadScene::Init()
{

	GET_SINGLE(ResourceManager)->LoadSound(L"DeadBGM", L"Sound\\Dead.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"DeadBGM");

	Object* background = new Background(L"BlackBackground", L"Texture\\BlackScreen.bmp", nullptr, 0);
	background->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	background->SetSize({ 1024.f,1024.f });
	AddObject(background, LAYER::BACKGROUND);

	Object* deadAnimation = new BackgroundAnimation(L"Texture\\YouDie.bmp", 10, { 1024,1024 }, 0.5f);
	deadAnimation->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 100 });
	deadAnimation->SetSize({ 1024.f,1024.f });
	AddObject(deadAnimation, LAYER::BACKGROUND);

	UI_Button* button = new UI_Button(L"Texture\\Button.bmp", L"Retry", { 0.25f,0.15f }, L"RetryButton", { 1,1 }, true);
	button->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	button->SetSize({ 150.f,40.f });
	button->OnClick = []() {
		GET_SINGLE(SceneManager)->LoadScene(L"BossTestScene");
		};
	AddObject(button, LAYER::UI);
	cout << "½ÃÀÛÇÔ";

}



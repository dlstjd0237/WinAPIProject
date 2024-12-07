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

	Object* deadAnimation = new BackgroundAnimation(L"Texture\\YouDie.bmp", 10, { 1024,1024 }, {0.5f, 0.5f});
	deadAnimation->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 100 });
	deadAnimation->SetSize({ 1024.f,1024.f });
	AddObject(deadAnimation, LAYER::BACKGROUND);

	UI_Button* button = new UI_Button(L"Texture\\DeadButton.bmp", L"Title", { 0.6f,0.6f }, L"RetryButton", { 1.9f,1.9f }, true);
	button->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 300 });
	button->SetSize({ 300.f,70.f });
	button->OnClick = []() {
		GET_SINGLE(SceneManager)->LoadScene(L"EntryScene");
		};
	AddObject(button, LAYER::UI);

}

void DeadScene::Release()
{
	Scene::Release();
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);

}



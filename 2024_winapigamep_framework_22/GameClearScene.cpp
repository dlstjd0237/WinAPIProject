#include "pch.h"
#include "GameClearScene.h"
#include "UI_Button.h"
#include "SceneManager.h"
#include "Background.h"
#include "BackgroundAnimation.h"
#include "ResourceManager.h"

void GameClearScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadSound(L"ClearBGM", L"Sound\\Clear.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"ClearBGM");


	Object* deadAnimation = new Background(L"Backgorund", L"Texture\\GameClear.bmp",nullptr,0 );
	deadAnimation->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f - 100 });
	deadAnimation->SetSize({ 1024.f,1024.f });
	AddObject(deadAnimation, LAYER::BACKGROUND);

	UI_Button* button = new UI_Button(L"Texture\\ShutDown.bmp", L"", { 0.6f,0.65f }, L"RetryButton", { 1.9f,1.9f }, true);
	button->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f +100 });
	button->SetSize({ 300.f,70.f });
	button->OnClick = []() {
		PostQuitMessage(0);
		};
	AddObject(button, LAYER::UI);

}

void GameClearScene::Release()
{
	Scene::Release();
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
}

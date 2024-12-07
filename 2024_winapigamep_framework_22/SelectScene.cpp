#include "pch.h"
#include "SelectScene.h"
#include "ResourceManager.h"
#include "UI_Button.h"
#include "SceneManager.h"
#include "Background.h"
void SelectScene::Init()
{
	GET_SINGLE(ResourceManager)->LoadSound(L"SelectBGM", L"Sound\\Dead.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"SelectBGM");

	Object* background = new Background(L"BlackBackground", L"Texture\\BlackScreen.bmp", nullptr, 0);
	background->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	background->SetSize({ 1024.f,1024.f });
	AddObject(background, LAYER::BACKGROUND);

	UI_Button* Boss1Button = new UI_Button(L"Texture\\Boss1Select.bmp", L"", { 1,1 }, L"Boss1Sel", { 0,0 }, false);
	Boss1Button->SetPos({ SCREEN_WIDTH / 2 - 300,SCREEN_HEIGHT / 2 });
	Boss1Button->OnClick = []()
		{
			GET_SINGLE(SceneManager)->LoadScene(L"Stage1BossScene");
		};
	AddObject(Boss1Button, LAYER::UI);

	UI_Button* Boss2Button = new UI_Button(L"Texture\\Boss2Select.bmp", L"", { 1,1 }, L"Boss2Sel", { 0,0 }, false);
	Boss2Button->SetPos({ SCREEN_WIDTH / 2 + 300,SCREEN_HEIGHT / 2 });
	Boss2Button->OnClick = []()
		{
			GET_SINGLE(SceneManager)->LoadScene(L"Stage2BossScene");
		};
	AddObject(Boss2Button, LAYER::UI);
}

void SelectScene::Release()
{
	Scene::Release();
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
}

#include "pch.h"
#include "EntryScene.h"
#include "Player.h"
#include "Background.h"
#include "SceneManager.h"
#include "UI_Button.h"
#include "TitleBossBG.h"
#include "Boss.h"

void EntryScene::Init()
{
    // BG Element=========
    Object* pPlayer = new Player;

    //보스안해~

	//보스안해~

	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Title.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");

	Object* pBackgroundObj1 = new Background(L"Sky", L"Texture\\sky.bmp", pPlayer, 0.f);
	pBackgroundObj1->SetPos({ (SCREEN_WIDTH / 2.f), (SCREEN_HEIGHT / 2.f) });
	AddObject(pBackgroundObj1, LAYER::BACKGROUND);

	Object* pBackgroundObj2 = new Background(L"Mountains", L"Texture\\mountains.bmp", pPlayer, 0.025f);
	pBackgroundObj2->SetPos({ (SCREEN_WIDTH / 2.f), (SCREEN_HEIGHT / 2.f) + 40 });
	AddObject(pBackgroundObj2, LAYER::BACKGROUND);

	// UI Element======

	Object* pTitle = new UI_Button(L"Texture\\Title.bmp", L"", { 0.9f, 0.9f },
		L"pTitle", { 1.f, 1.f }, false);
	pTitle->SetPos({ SCREEN_WIDTH / 4.5f, 170.f });
	AddObject(pTitle, LAYER::UI);

    UI_Button* pStartButton = new UI_Button(L"Texture\\Button.bmp", L"\n\nSTART", { 0.3f, 0.3f },
        L"pStartButton", { 1.f, 1.f }, true);
    pStartButton->SetPos({ SCREEN_WIDTH / 9.f, 515.f });
    pStartButton->OnClick = []()
        {
            GET_SINGLE(SceneManager)->LoadScene(L"BossTestScene");
        };
    AddObject(pStartButton, LAYER::UI);

    UI_Button* pExitButton = new UI_Button(L"Texture\\Button.bmp", L"\n\nEXIT", { 0.3f, 0.3f },
        L"pExitButton", { 1.f, 1.f }, true);
    pExitButton->SetPos({ SCREEN_WIDTH / 9.f, 630.f });
    pExitButton->OnClick = []()
        {
            PostQuitMessage(0);
        };
    AddObject(pExitButton, LAYER::UI);
}

void EntryScene::Update()
{
	Scene::Update(); // 기본적인 Scene 업데이트 호출
}

void EntryScene::Release() {
	Scene::Release();
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);

}
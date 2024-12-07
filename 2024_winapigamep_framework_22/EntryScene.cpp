#include "pch.h"
#include "EntryScene.h"
#include "Player.h"
#include "Background.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "UI_Button.h"
#include "TitleBossBG.h"
#include "Boss.h"

void EntryScene::Init()
{
    // BG Element=========
    Object* pPlayer = new Player;

    //보스안해~

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

    //Object* pBgBoss = new UI_Button(L"Texture\\BossBG.bmp", L"", { 3.5f, 3.5f },
    //    L"pBgBoss", { 1.f, 1.f }, false);
    //pBgBoss->SetPos({ SCREEN_WIDTH / 1.3f, 190.f });
    //AddObject(pBgBoss, LAYER::UI);

    Object* pPaper = new UI_Button(L"Texture\\Paper.bmp", L"\n\n\n MOVE : WASD\n\n JUMP : SPACE\n\n ATTACK : MOUSE LEFT\n\n\n DEVELOPERs\nI.S BEAK, I.H LEE, J.M JANG",
        { 0.85f, 0.85f },
        L"pPaper", { 1.f, 1.f }, false);
    pPaper->SetPos({ SCREEN_WIDTH / 1.15f, 560.f });
    AddObject(pPaper, LAYER::UI);

    UI_Button* pStartButton = new UI_Button(L"Texture\\Button.bmp", L"\n\nSTART", { 0.3f, 0.3f },
        L"pStartButton", { 1.f, 1.f }, true);
    pStartButton->SetPos({ SCREEN_WIDTH / 9.f, 515.f });
    pStartButton->OnClick = []()
    {
        GET_SINGLE(EventManager)->SceneLoad(L"Stage1BossScene");
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

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

    // TitleBossBG 생성 (보스를 가만히 Idle 애니메이션으로 설정)
    TitleBossBG* pBossBG = new TitleBossBG();
    pBossBG->SetPos({ SCREEN_WIDTH / 2.f, 150.f }); // 위치 설정
    AddObject(pBossBG, LAYER::ENEMY); // ENEMY 레이어에 추가

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

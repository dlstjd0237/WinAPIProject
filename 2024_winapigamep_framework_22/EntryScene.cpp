#include "pch.h"
#include "EntryScene.h"
#include "Ground.h"
#include "Player.h"
#include "Background.h"
#include "SceneManager.h"

void EntryScene::Init()
{
	//BG Elemant=========

	Object* pPlayer = new Player;

	/*Object* pObj = new Ground;
	pObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pObj->SetSize({ 1400.f, 720.f });
	pObj->SetName(L"Ground");
	AddObject(pObj, LAYER::GROUND);*/

	Object* pBackgroundObj1 = new Background(L"Sky", L"Texture\\sky.bmp",
		{ 4.5f,4.5f }, pPlayer, 0.f);
	pBackgroundObj1->SetPos({ (SCREEN_WIDTH / 2.f) - 20, (SCREEN_HEIGHT / 2.f) + 150 });
	AddObject(pBackgroundObj1, LAYER::BACKGROUND);

	Object* pBackgroundObj2 = new Background(L"Mountains", L"Texture\\mountains.bmp",
		{ 4.5f,4.5f }, pPlayer, 0.025f);
	pBackgroundObj2->SetPos({ (SCREEN_WIDTH / 2.f) - 90, (SCREEN_HEIGHT / 2.f) + 50 });
	AddObject(pBackgroundObj2, LAYER::BACKGROUND);

	Object* pBackgroundObj3 = new Background(L"Tees", L"Texture\\trees.bmp",
		{ 4.5f,4.5f }, pPlayer, 0.075f);
	pBackgroundObj3->SetPos({ SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 2.f) + 30 });
	AddObject(pBackgroundObj3, LAYER::BACKGROUND);

	//UI Element======

	Object* pStartButton = new UI_Button(L"Texture\\Button.bmp", L"START", { 0.3f, 0.3f });
	pStartButton->SetPos({ SCREEN_WIDTH / 2.f, 550.f });
	pStartButton->SetSize({ 620.f, 40.f });
	AddObject(pStartButton, LAYER::UI);
}

void EntryScene::Update()
{
}

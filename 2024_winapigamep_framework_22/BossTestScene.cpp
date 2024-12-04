#include "pch.h"
#include "BossTestScene.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Stage1Boss.h"
#include "Boss.h"
#include "Player.h"
#include "Ground.h"
#include "WarningPanel.h"
#include "Background.h"

void BossTestScene::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pPlayer->SetSize({ 44.f, 69.f });
	AddObject(pPlayer, LAYER::PLAYER);

	Boss* boss = new Stage1Boss();
	boss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	boss->SetSize({ 50.f,50.f });
	AddObject(boss, LAYER::ENEMY);

	WarningPanel* warning = new WarningPanel(0.5f, { SCREEN_WIDTH / 2.f + 50.f, 150.f }, { 100.f,500.f });
	AddObject(warning, LAYER::DEFAULT);
	warning->isFade = true;

	Object* pObj = new Ground;
	pObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pObj->SetSize({ 1400.f, 720.f });
	pObj->SetName(L"Ground");
	AddObject(pObj, LAYER::GROUND);

	Object* pBackgroundObj1 = new Background(L"Sky", L"Texture\\sky.bmp", { 4.5f,4.5f });
	pBackgroundObj1->SetPos({ (SCREEN_WIDTH / 2.f) - 20, (SCREEN_HEIGHT / 2.f) + 150 });
	AddObject(pBackgroundObj1, LAYER::BACKGROUND);

	Object* pBackgroundObj2 = new Background(L"Mountains", L"Texture\\mountains.bmp", { 4.5f,4.5f });
	pBackgroundObj2->SetPos({ (SCREEN_WIDTH / 2.f) - 90, (SCREEN_HEIGHT / 2.f) + 50 });
	AddObject(pBackgroundObj2, LAYER::BACKGROUND);

	Object* pBackgroundObj3 = new Background(L"trees", L"Texture\\trees.bmp", { 4.5f,4.5f });
	pBackgroundObj3->SetPos({ SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 2.f) + 30 });
	AddObject(pBackgroundObj3, LAYER::BACKGROUND);

	pUIHealth->SetPos({ SCREEN_WIDTH / 3.f, 1000.f });
	pUIHealth->SetSize({ 620.f, 40.f });
	pUIHealth->SetFillAmount(1.f);

	AddObject(pUIHealth, LAYER::UI);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
}

void BossTestScene::Update()
{
	Scene::Update();
}

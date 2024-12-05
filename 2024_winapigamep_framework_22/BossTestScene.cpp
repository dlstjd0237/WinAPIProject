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
#include "UI_Button.h"
#include "UI_Health.h"

void BossTestScene::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pPlayer->SetSize({ 44.f, 69.f });
	AddObject(pPlayer, LAYER::PLAYER);
	pPlayer->SetName(L"Player");

	Boss* boss = new Stage1Boss();
	boss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	AddObject(boss, LAYER::ENEMY);
	boss->SetName(L"Enemy");

	//WarningPanel* war = new WarningPanel(0.1f, { SCREEN_WIDTH + 500.f , SCREEN_HEIGHT / 2.f }, { SCREEN_WIDTH, 50});
	//AddObject(war, LAYER::DEFAULT);
	//war->SetRotate({ -1,-1 });

	Object* pObj = new Ground;
	pObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pObj->SetSize({ 1400.f, 720.f });
	pObj->SetName(L"Ground");
	AddObject(pObj, LAYER::GROUND);

	//==== Background Setting ====

	//Object* pBackgroundObj1 = new Background(L"Sky", L"Texture\\sky.bmp",
	//	{ 4.5f,4.5f }, pPlayer, 0.f);
	//pBackgroundObj1->SetPos({ (SCREEN_WIDTH / 2.f) - 20, (SCREEN_HEIGHT / 2.f) + 150 });
	//AddObject(pBackgroundObj1, LAYER::BACKGROUND);

	//Object* pBackgroundObj2 = new Background(L"Mountains", L"Texture\\mountains.bmp",
	//	{ 4.5f,4.5f }, pPlayer, 0.025f);
	//pBackgroundObj2->SetPos({ (SCREEN_WIDTH / 2.f) - 90, (SCREEN_HEIGHT / 2.f) + 50 });
	//AddObject(pBackgroundObj2, LAYER::BACKGROUND);

	//Object* pBackgroundObj3 = new Background(L"Tees", L"Texture\\trees.bmp",
	//	{ 4.5f,4.5f }, pPlayer, 0.075f);
	//pBackgroundObj3->SetPos({ SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 2.f) + 30 });
	//AddObject(pBackgroundObj3, LAYER::BACKGROUND);

	//============================

	Object* pUIHealth = new UI_Health(L"Texture\\plane.bmp", L"Texture\\planem.bmp");
	pUIHealth->SetPos({ SCREEN_WIDTH / 3.f, 600.f });
	pUIHealth->SetSize({ 620.f, 40.f });
	AddObject(pUIHealth, LAYER::UI);

	Object* pUIButton = new UI_Button(L"Texture\\planem.bmp");
	pUIButton->SetPos({ SCREEN_WIDTH / 3.f, 550.f });
	pUIButton->SetSize({ 620.f, 40.f });
	AddObject(pUIButton, LAYER::UI);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ATTACKEFFECT, LAYER::ENEMY);
}

void BossTestScene::Update()
{
	Scene::Update();
}

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


	//==== Ground Setting ====
	Object* pObj = new Ground(true, { 1920, 50 }, { 0, 280 });
	pObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pObj->SetSize({ 1400.f, 720.f });
	pObj->SetName(L"Ground");
	AddObject(pObj, LAYER::GROUND);
	//========================


	//==== Wall Setting ====
	Object* pLeftWallObj = new Ground(false, { 50.f, 900.f }, { 0, 0 });
	pLeftWallObj->SetPos({ -25.f, SCREEN_HEIGHT / 2.f });
	pLeftWallObj->SetSize({ 50.f, 900.f });
	pLeftWallObj->SetName(L"LeftWall");
	AddObject(pLeftWallObj, LAYER::GROUND);

	Object* pRightWallObj = new Ground(false, { 50.f, 900.f }, { 0, 0 });
	pRightWallObj->SetPos({ 1425.f, SCREEN_HEIGHT / 2.f });
	pRightWallObj->SetSize({ 50.f, 900.f });
	pRightWallObj->SetName(L"RightWall");
	AddObject(pRightWallObj, LAYER::GROUND);
	//======================




	//==== Background Setting ====

	Object* pBackgroundObj1 = new Background(L"Sky", L"Texture\\Sky_mountains.bmp",
		pPlayer, 0.f);
	pBackgroundObj1->SetPos({ (SCREEN_WIDTH / 2.f) , (SCREEN_HEIGHT / 2.f) });
	AddObject(pBackgroundObj1, LAYER::BACKGROUND);

	Object* pBackgroundObj3 = new Background(L"Tees", L"Texture\\trees.bmp",
		pPlayer, 0.075f);
	pBackgroundObj3->SetPos({ SCREEN_WIDTH / 2.f, (SCREEN_HEIGHT / 2.f) - 50 });
	AddObject(pBackgroundObj3, LAYER::BACKGROUND);

	//============================

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::PROJECTILE);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ENEMY, LAYER::ATTACKEFFECT);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ATTACKEFFECT, LAYER::ENEMY);
}

void BossTestScene::Update()
{
	Scene::Update();
}

#include "pch.h"
#include "Stage2BossScene.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Stage2Boss.h"
#include "Boss.h"
#include "Player.h"
#include "Ground.h"
#include "WarningPanel.h"
#include "Background.h"
#include "UI_Button.h"
#include "UI_Health.h"
#include "Laser.h"

void Stage2BossScene::Init()
{
	Player* pPlayer = new Player(pPlayerHealth, pPlayerEnergy);
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f + 200.f });
	pPlayer->SetSize({ 44.f, 69.f });
	AddObject(pPlayer, LAYER::PLAYER);
	pPlayer->SetName(L"Player");

	Boss* boss = new Stage2Boss();
	boss->SetHealth(pBossHealth);
	boss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	AddObject(boss, LAYER::ENEMY);
	boss->SetName(L"Enemy");

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

	pPlayerHealth->SetPos({ 200.f, 665.f });
	pPlayerHealth->SetFillAmount(1.f);
	AddObject(pPlayerHealth, LAYER::UI);

	pPlayerEnergy->SetPos({ 1200.f, 665.f });
	pPlayerEnergy->SetFillAmount(0.5f);
	AddObject(pPlayerEnergy, LAYER::UI);

	pBossHealth->SetPos({ SCREEN_WIDTH / 2.f, 45.f });
	pBossHealth->SetFillAmount(1.f);
	AddObject(pBossHealth, LAYER::UI);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::Laser);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::ATTACKEFFECT, LAYER::ENEMY);
	
	GET_SINGLE(ResourceManager)->LoadSound(L"Stage2BGM", L"Sound\\Stage2.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"Stage2BGM");
}

void Stage2BossScene::Update()
{
	Scene::Update();
}

void Stage2BossScene::Release()
{
	Scene::Release();
	GET_SINGLE(ResourceManager)->Stop(SOUND_CHANNEL::BGM);
}
#include "pch.h"
#include "BossTestScene.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Stage1Boss.h"
#include "Boss.h"
#include "Player.h"
#include "Ground.h"
#include "WarningPanel.h"

void BossTestScene::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });
	pPlayer->SetSize({ 5.f, 5.f });
	AddObject(pPlayer, LAYER::PLAYER);
	pPlayer->SetName(L"Player");

	Boss* boss = new Stage1Boss();
	boss->SetPos({ SCREEN_WIDTH / 2.f, 150.f });
	AddObject(boss, LAYER::ENEMY);
	boss->SetName(L"Enemy");

	WarningPanel* warning = new WarningPanel(0.5f, { SCREEN_WIDTH / 2.f + 50.f, 150.f }, { 100.f,500.f });
	AddObject(warning, LAYER::DEFAULT);
	warning->isFade = true;

	Object* pObj = new Ground;
	pObj->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT /2.f + 300 });
	pObj->SetSize({ 1920.f, 50.f });
	pObj->SetName(L"Ground");
	AddObject(pObj, LAYER::GROUND);

	pUIHealth->SetPos({ SCREEN_WIDTH / 3.f, 1000.f });
	pUIHealth->SetSize({ 620.f, 40.f });
	pUIHealth->SetFillAmount(1.f);

	AddObject(pUIHealth, LAYER::UI);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PROJECTILE);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::PROJECTILE);
}

void BossTestScene::Update()
{
	Scene::Update();
}

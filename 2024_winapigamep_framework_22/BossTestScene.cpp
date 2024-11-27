#include "pch.h"
#include "BossTestScene.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "Stage1Boss.h"
#include "Boss.h"
#include "Player.h"
#include "Ground.h"

void BossTestScene::Init()
{
	Object* pPlayer = new Player;
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 100.f,100.f });
	AddObject(pPlayer, LAYER::PLAYER);

	Object* boss = new Stage1Boss();
	boss->SetPos({ SCREEN_WIDTH / 2.f ,150.f });
	boss->SetSize({ 100.f,100.f });
	AddObject(boss, LAYER::ENEMY);

	Object* pObj = new Ground;
	pObj->SetPos({ SCREEN_WIDTH / 2.f, 550.f });
	pObj->SetSize({ 1920.f, 100.f });
	pObj->SetName(L"Ground");
	AddObject(pObj, LAYER::GROUND);

	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
}

void BossTestScene::Update()
{
	Scene::Update();
}

#include "pch.h"
#include "BossTestScene.h"
#include "SceneManager.h"
#include "Stage1Boss.h"
#include "Boss.h"
#include "Player.h"

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
}

void BossTestScene::Update()
{
	Scene::Update();
}

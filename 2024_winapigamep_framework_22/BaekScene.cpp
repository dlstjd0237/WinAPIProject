#include "pch.h"
#include "BaekScene.h"
#include "Object.h"
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "Ground.h"
#include "CollisionManager.h"
#include "ResourceManager.h"
void BaekScene::Init()
{
	Object* pPlayer = new Player(NULL);
	pPlayer->SetPos({ SCREEN_WIDTH / 2.f,500.f });
	pPlayer->SetSize({ 69.f*2,44.f*2 });
	pPlayer->SetName(L"Player");
	AddObject(pPlayer, LAYER::PLAYER);


	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PROJECTILE, LAYER::ENEMY);
	GET_SINGLE(CollisionManager)->CheckLayer(LAYER::GROUND, LAYER::PLAYER);
	//GET_SINGLE(CollisionManager)->CheckLayer(LAYER::PLAYER, LAYER::ENEMY);
	GET_SINGLE(ResourceManager)->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	GET_SINGLE(ResourceManager)->Play(L"BGM");
}

//void BaekScene::Update() {
//
//	Scene::Update();
//	if (GET_KEYDOWN(KEY_TYPE::ENTER))
//		GET_SINGLE(SceneManager)->LoadScene(L"GameScene");
//}
//
//void BaekScene::Init()
//{
//}

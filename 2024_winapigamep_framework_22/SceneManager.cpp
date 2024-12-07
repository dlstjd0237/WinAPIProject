#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "BaekScene.h"
#include "Stage1BossScene.h"
#include "Stage2BossScene.h"
#include "EntryScene.h"
#include "DeadScene.h"

void SceneManager::Init()
{
	m_pCurrentScene = nullptr;

	// �� ���
	
	RegisterScene(L"TitleScene",std::make_shared<TitleScene>());
	RegisterScene(L"GameScene",std::make_shared<GameScene>());
	RegisterScene(L"Stage1BossScene",std::make_shared<Stage1BossScene>());
	RegisterScene(L"Stage2BossScene",std::make_shared<Stage2BossScene>());
	RegisterScene(L"BaekScene",std::make_shared<BaekScene>());
	RegisterScene(L"EntryScene",std::make_shared<EntryScene>());
	RegisterScene(L"DeadScene", std::make_shared<DeadScene>());

	LoadScene(L"DeadScene");
	//LoadScene(L"EntryScene");
	//LoadScene(L"BossTestScene");
	//LoadScene(L"TitleScene");
}

void SceneManager::Update()
{
	if (m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->Update();
	m_pCurrentScene->LateUpdate();
}

void SceneManager::Render(HDC _hdc)
{
	if (m_pCurrentScene == nullptr)
		return;
	m_pCurrentScene->Render(_hdc);
}


void SceneManager::RegisterScene(const wstring& _sceneName, std::shared_ptr<Scene> _scene)
{
	if (_sceneName.empty() || _scene == nullptr)
		return;
	m_mapScenes.insert(m_mapScenes.end(), {_sceneName, _scene});
}

void SceneManager::LoadScene(const wstring& _sceneName)
{
	if (m_pCurrentScene != nullptr)
	{
		m_pCurrentScene->Release();
		m_pCurrentScene = nullptr;
	}

	auto iter = m_mapScenes.find(_sceneName);
	if (iter != m_mapScenes.end())
	{
		m_pCurrentScene = iter->second;
		m_pCurrentScene->Init();
	}
}

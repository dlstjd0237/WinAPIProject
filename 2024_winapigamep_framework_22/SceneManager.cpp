#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "BaekScene.h"
#include "Stage1BossScene.h"
#include "Stage2BossScene.h"
#include "EntryScene.h"
#include "DeadScene.h"
#include "LoadingPanel.h"
#include "TimeManager.h"
#include "GameClearScene.h"
#include "SelectScene.h"

void SceneManager::Init()
{
	m_pCurrentScene = nullptr;

	RegisterScene(L"Stage1BossScene", std::make_shared<Stage1BossScene>());
	RegisterScene(L"Stage2BossScene", std::make_shared<Stage2BossScene>());
	RegisterScene(L"EntryScene", std::make_shared<EntryScene>());
	RegisterScene(L"DeadScene", std::make_shared<DeadScene>());
	RegisterScene(L"GameClearscene", std::make_shared<GameClearScene>());
	RegisterScene(L"SelectScene", std::make_shared<SelectScene>());

	LoadScene(L"EntryScene");
}

void SceneManager::Update()
{
	if(!_loadingPanel->GetIsDead())
		_loadingPanel->Update();

	if (_loadingPanel->isComplete && _loadingPanel->isFadeIn)
	{
		m_pCurrentScene->Release();
		m_pCurrentScene = NULL;

		auto iter = m_mapScenes.find(_loadSceneName);
		if (iter != m_mapScenes.end())
		{
			_loadingPanel = new LoadingPanel();
			_loadingPanel->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
			_loadingPanel->SetPos({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });

			m_pCurrentScene = iter->second;
			m_pCurrentScene->AddObject(_loadingPanel, LAYER::LoadingPanel);
			m_pCurrentScene->Init();

			_loadingPanel->Load(false, 1.f, 1.f);
		}
	}
	else
	{
		if (m_pCurrentScene == nullptr || _loadingPanel->isFadeIn)
			return;
		m_pCurrentScene->Update();
		m_pCurrentScene->LateUpdate();
	}
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
	m_mapScenes.insert(m_mapScenes.end(), { _sceneName, _scene });
}

void SceneManager::LoadScene(const wstring& _sceneName)
{
	_loadSceneName = _sceneName;
	if (m_pCurrentScene != nullptr)
	{
		_loadingPanel->Load(true, 1.f);
	}
	else
	{
		auto iter = m_mapScenes.find(_sceneName);
		if (iter != m_mapScenes.end())
		{
			_loadingPanel = new LoadingPanel();
			_loadingPanel->SetSize({ SCREEN_WIDTH, SCREEN_HEIGHT });
			_loadingPanel->SetPos({ (float)-SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });

			m_pCurrentScene = iter->second;
			m_pCurrentScene->AddObject(_loadingPanel, LAYER::LoadingPanel);
			m_pCurrentScene->Init();
		}
	}
}

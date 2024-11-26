#include "pch.h"
#include "ResourceManager.h"
#include "Core.h"
#include "Texture.h"
void ResourceManager::Init()
{
	::GetCurrentDirectory(255, m_resourcePath);
	wcscat_s(m_resourcePath, 255, L"\\Resource\\");
	//::SetWindowText(GET_SINGLE(Core)->GetHwnd(), m_resourcePath);

 	FMOD::System_Create(&m_pSoundSystem); // �ý��� ���� �Լ�
	// ä�μ�, ���� ���
	if (m_pSoundSystem != nullptr)
		m_pSoundSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);

}

Texture* ResourceManager::TextureLoad(const wstring& _key, const wstring& _path)
{
	Texture* pTex = TextureFind(_key);
	if (nullptr != pTex)
		return pTex;

	// ����� �����Դϴ�. ������ּ���.
	// 1. ��� ����
	wstring texpath = m_resourcePath;
	texpath += _path;
	
	// 2. Texture ��������?
	pTex = new Texture;
	pTex->Load(texpath);
	pTex->SetKey(_key);
	pTex->SetPath(texpath);
	m_mapTextures.insert({_key,pTex});
	return pTex;
}

Texture* ResourceManager::TextureFind(const wstring& _key)
{
	auto iter = m_mapTextures.find(_key);
	if (iter != m_mapTextures.end())
		return iter->second;
	return nullptr;
}

void ResourceManager::Release()
{
	map<wstring, Texture*>::iterator iter;
	for (iter = m_mapTextures.begin(); iter != m_mapTextures.end(); ++iter)
		delete iter->second;
	m_mapTextures.clear();

	// SOUND
	map<wstring, tSoundInfo*>::iterator itersod;
	for (itersod = m_mapSounds.begin(); itersod != m_mapSounds.end(); ++itersod)
	{
		if (nullptr != itersod->second)
			delete itersod->second;
	}
	m_mapSounds.clear();

	// �� ���� �� �� �ý��� �ݰ� ��ȯ
	m_pSoundSystem->close();
	m_pSoundSystem->release();
}

void ResourceManager::LoadSound(const wstring& _key, const wstring& _path, bool _isLoop)
{
	if (FindSound(_key))
		return;
	wstring strFilePath = m_resourcePath;
	strFilePath += _path;

	// wstring to string
	std::string str;
	str.assign(strFilePath.begin(), strFilePath.end());

	// �������� ���� ����
	FMOD_MODE eMode = FMOD_LOOP_NORMAL; // �ݺ� ���
	if (!_isLoop)
		eMode = FMOD_DEFAULT; // ���� 1���� ���

	tSoundInfo* ptSound = new tSoundInfo;
	ptSound->IsLoop = _isLoop;
	// ���� ��ü�� ����� ���� system��.
							//���ϰ��,  FMOD_MODE, NULL, &sound
	m_pSoundSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
	m_mapSounds.insert({ _key, ptSound });
}

void ResourceManager::Play(const wstring& _key)
{
	tSoundInfo* ptSound = FindSound(_key);
	if (!ptSound)
		return;
	m_pSoundSystem->update(); // play�Ҷ� update�� �ֱ������� ȣ���ؾ� ���尡 �������� ����.
	SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
	if (!ptSound->IsLoop)
		eChannel = SOUND_CHANNEL::EFFECT;
	// ���� ��� �Լ�. &channel�� � ä���� ���� ����Ǵ��� ������ �ѱ�
	m_pSoundSystem->playSound(ptSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);
}

void ResourceManager::Stop(SOUND_CHANNEL _channel)
{
	m_pChannel[(UINT)_channel]->stop();
}

void ResourceManager::Volume(SOUND_CHANNEL _channel, float _vol)
{
	// 0.0 ~ 1.0 ���� ����
	m_pChannel[(UINT)_channel]->setVolume(_vol);
}

void ResourceManager::Pause(SOUND_CHANNEL _channel, bool _ispause)
{
	// bool���� true�� �Ͻ�����. ��, �� �Լ��� ������ Createsound�Ҷ� 
// FMOD_MODE�� FMOD_LOOP_NORMAL �̾�� ��.
	m_pChannel[(UINT)_channel]->setPaused(_ispause);
}

tSoundInfo* ResourceManager::FindSound(const wstring& _key)
{
	map<wstring, tSoundInfo*>::iterator iter = m_mapSounds.find(_key);

	if (iter == m_mapSounds.end())
		return nullptr;
	return iter->second;
}

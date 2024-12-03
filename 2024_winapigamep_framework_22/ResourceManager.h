#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
enum class SOUND_CHANNEL //���帶�� ä��
{
	BGM, EFFECT, END
};
struct tSoundInfo
{
	FMOD::Sound* pSound; // ���� ���� �޸�
	bool IsLoop;		// ���帶�� ������������
};
class Texture;
class ResourceManager
{
	DECLARE_SINGLE(ResourceManager);
public:
	void Init();
	const wchar_t* GetResPath() const { return m_resourcePath; }
public:
	Texture* TextureLoad(const wstring& _key, const wstring& _path);
	Texture* TextureFind(const wstring& _key);
	void Release();
public:
	void LoadSound(const wstring& _key, const wstring& _path, bool _isLoop);
	void Play(const wstring& _key);
	void Stop(SOUND_CHANNEL _channel);
	void Volume(SOUND_CHANNEL _channel, float _vol);
	void Pause(SOUND_CHANNEL _channel, bool _ispause);

private:
	tSoundInfo* FindSound(const wstring& _key);
private:
	wchar_t m_resourcePath[255] = {};
	map<wstring, Texture*> m_mapTextures;
	map<wstring, tSoundInfo*> m_mapSounds;
	FMOD::System* m_pSoundSystem; // ���� �ý���
	FMOD::Channel* m_pChannel[(UINT)SOUND_CHANNEL::END]; // ����� ä��
public:
	const float& GetAnimationScale(const wstring& animName) {
		if (m_animationScales.contains(animName) == true)
			return m_animationScales[animName];
		return 1;
	}
	const bool& GetAnimationFlip(const wstring& animName) {
		if (m_animationFilps.contains(animName) == true)
			return m_animationFilps[animName];
		return false;
	}
	const void SetAnimationScale(const wstring& animName, float scale) {
		if (m_animationScales.contains(animName) == true)
			m_animationScales[animName] = scale;
	}
public:
	void AddAnimationScale(const wstring& key, float& value) { m_animationScales[key] = value; }
	void AddAnimationFlips(const wstring& key, bool& value) { m_animationFilps[key] = value; }
private:
	map<wstring, float> m_animationScales;
	map<wstring, bool> m_animationFilps;
};


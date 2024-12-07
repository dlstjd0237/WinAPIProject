#include "pch.h"
#include "BackgroundAnimation.h"
#include "Animator.h"
#include"ResourceManager.h"
BackgroundAnimation::BackgroundAnimation(wstring _texturPath, int _fram ,
	Vec2 _texturSliceSize, Vec2 _scale)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"BackgroundAnimation", _texturPath);

	this->AddComponent<Animator>();
	this->GetComponent<Animator>()->CreateAnimation(L"BackgroundAnimationMove", m_pTex, { 0.f,0.f },
		_texturSliceSize, { _texturSliceSize.x,0.f }, _fram, 0.15f, false, { _scale ,_scale });
	this->GetComponent<Animator>()->PlayAnimation(L"BackgroundAnimationMove", false);
}

BackgroundAnimation::~BackgroundAnimation()
{
}

void BackgroundAnimation::Update()
{
}

void BackgroundAnimation::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

#include "pch.h"
#include "TitleBossBG.h"
#include "Animation.h"
#include "Animator.h"
#include "Collider.h"

TitleBossBG::TitleBossBG()
{
	_m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"bbbbbb", L"Texture\\Boss1.bmp");

	GetComponent<Animator>()->CreateAnimation(L"IdleRight", _m_pTex, Vec2(0.f, 0.f),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, false, {3,3}, {0.f, -128.f / 2});
	GetComponent<Animator>()->CreateAnimation(L"IdleLeft", _m_pTex, Vec2(0.f, 128.f * 7),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, true, {3,3}, {0.f, -128.f / 2});


	SetSize(Vec2(160.f, 128.f));

	BossMovePointInit();

	GetComponent<Animator>()->PlayAnimation(L"IdleLeft", true);
	GetComponent<Collider>()->SetSize({ 160.f / 2, 128.f });
}

void TitleBossBG::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void TitleBossBG::PatternInit()
{

}
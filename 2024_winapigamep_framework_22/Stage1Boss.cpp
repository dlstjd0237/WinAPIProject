#include "pch.h"
#include "Stage1Boss.h"
#include "BossPattern.h"
#include "CircleBossPattern.h"
#include "TimeManager.h"
#include "Collider.h"
#include "OneShotPattern.h"

Stage1Boss::Stage1Boss()
{
	_patternDelay = 3.f;

	PatternInit();
	PatternIdxInit();

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Boss1", L"Texture\\Boss1.bmp");

	GetComponent<Animator>()->CreateAnimation(L"Boss1RightIdle", m_pTex, Vec2(0.f, 0.f),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, false, 3);
	GetComponent<Animator>()->CreateAnimation(L"Boss1LeftIdle", m_pTex, Vec2(0.f, 0.f),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, true, 3);
	GetComponent<Animator>()->CreateAnimation(L"Boss1RightMove", m_pTex, Vec2(0.f, 128.f),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, false, 3);
	GetComponent<Animator>()->CreateAnimation(L"Boss1LeftMove", m_pTex, Vec2(0.f, 128.f),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, true, 3);
	GetComponent<Animator>()->PlayAnimation(L"Boss1RightIdle", true);

	GetComponent<Collider>()->SetSize({ 69.f * 2 - 15, 44.f * 3 });
	GetComponent<Collider>()->SetOffSetPos({ 0.f, 128.f / 2 });
}

void Stage1Boss::PatternInit()
{
	CircleBossPattern* circlePat = new CircleBossPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::CircleShot, circlePat);
	
	OneShotPattern* oneShotPat = new OneShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::OneShot, oneShotPat);

	for (auto iter = _bossPattern.begin(); iter != _bossPattern.end(); iter++)
	{
		iter->second->Init(this);
	}
}

void Stage1Boss::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

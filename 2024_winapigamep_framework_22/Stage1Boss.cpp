#include "pch.h"
#include "Stage1Boss.h"
#include "BossPattern.h"
#include "TimeManager.h"
#include "Collider.h"
#include "AllRangeCircleBossPattern.h"
#include "OneShotPattern.h"
#include "CrossShotPattern.h"
#include "FollowBulletPattern.h"
#include "SniperShotPattern.h"
#include "BottomShotPattern.h"
#include "FollowBottomShotPattern.h"
#include "FallingShotPattern.h"
#include "CrossTargetShotPattern.h"

Stage1Boss::Stage1Boss()
{
	_patternDelay = 4.f;

	PatternInit();
	PatternIdxInit();

	_m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Boss1", L"Texture\\Boss1.bmp");
	_animScale = { 3,3 };

	GetComponent<Animator>()->CreateAnimation(L"IdleRight", _m_pTex, Vec2(0.f, 0.f),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, false, _animScale, { 0.f, -128.f / 2 });
	GetComponent<Animator>()->CreateAnimation(L"IdleLeft", _m_pTex, Vec2(0.f, 128.f * 7),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, false, _animScale, { 0.f, -128.f / 2 });

	GetComponent<Animator>()->CreateAnimation(L"MoveRight", _m_pTex, Vec2(0.f, 128.f),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, false, _animScale, { 0.f, -128.f / 2 });
	GetComponent<Animator>()->CreateAnimation(L"MoveLeft", _m_pTex, Vec2(0.f, 128.f * 8),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 8, 0.1f, false, _animScale, { 0.f, -128.f / 2 });

	GetComponent<Animator>()->CreateAnimation(L"AttackRight", _m_pTex, Vec2(0.f, 128.f * 2),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 13, 0.1f, false, _animScale, { 0.f, -128.f / 2 });
	GetComponent<Animator>()->CreateAnimation(L"AttackLeft", _m_pTex, Vec2(0.f, 128.f * 9),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 13, 0.1f, false, _animScale, { 0.f, -128.f / 2 });

	GetComponent<Animator>()->CreateAnimation(L"DamagedRight", _m_pTex, Vec2(0.f, 128.f * 5),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 5, 0.1f, false, _animScale, { 0.f, -128.f / 2 });
	GetComponent<Animator>()->CreateAnimation(L"DamagedLeft", _m_pTex, Vec2(0.f, 128.f * 12),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 5, 0.1f, false, _animScale, { 0.f, -128.f / 2 });

	GetComponent<Animator>()->CreateAnimation(L"DeadRight", _m_pTex, Vec2(0.f, 128.f * 6),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 9, 0.25f, false, _animScale, { 0.f, -128.f / 2 });
	GetComponent<Animator>()->CreateAnimation(L"DeadLeft", _m_pTex, Vec2(0.f, 128.f * 13),
		Vec2(160.f, 128.f), Vec2(160.f, 0.f), 9, 0.25f, false, _animScale, { 0.f, -128.f / 2 });

	SetSize(Vec2(160.f, 128.f));

	BossMovePointInit();

	GetComponent<Animator>()->PlayAnimation(L"IdleRight", true);
	GetComponent<Collider>()->SetSize({ 160.f / 2, 128.f });
}

void Stage1Boss::PatternInit()
{
	AllRangeCircleBossPattern* circlePat = new AllRangeCircleBossPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::AllRangeCircleShot, circlePat);
	
	OneShotPattern* oneShotPat = new OneShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::OneShot, oneShotPat);

	CrossShotPattern* crossShotPat = new CrossShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::CrossShot, crossShotPat);

	FollowBulletPattern* followShotPat = new FollowBulletPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::FollowShot, followShotPat);

	SniperShotPattern* sniperShotPat = new SniperShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::SniperShot, sniperShotPat);

	BottomShotPattern* bottomShotPat = new BottomShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::BottomShot, bottomShotPat);

	FollowBottomShotPattern* followBottomPat = new FollowBottomShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::FollowBottomShot, followBottomPat);

	FallingShotPattern* fallingShotPat = new FallingShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::FallingShot, fallingShotPat);

	CrossTargetShotPattern* crossTargetShotPat = new CrossTargetShotPattern();
	AddPattern<Stage1BossPattern>(Stage1BossPattern::CrossTargetShot, crossTargetShotPat);

	for (auto iter = _bossPattern.begin(); iter != _bossPattern.end(); iter++)
	{
		iter->second->Init(this);
	}
}

void Stage1Boss::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

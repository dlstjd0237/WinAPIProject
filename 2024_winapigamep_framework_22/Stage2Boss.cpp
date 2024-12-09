#include "pch.h"
#include "Stage2Boss.h"
#include "BossPattern.h"
#include "TimeManager.h"
#include "Collider.h"
#include "RandomLaserPattern.h"
#include "LeftFullLaserPattern.h"
#include "RightFullLaserPattern.h"
#include "CenterFullLaserPattern.h"
#include "ZigzagLaserPattern.h"
#include "ZigzagRandomLaserPattern.h"

Stage2Boss::Stage2Boss()
{
	_patternDelay = 4.f;

	PatternInit();
	PatternIdxInit();

	_m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Boss2Right", L"Texture\\Boss2Right.bmp");
	_leftTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Boss2Left", L"Texture\\Boss2Left.bmp");

	_animScale = { 2.5f, 2.5f };
	float sliceHeight = 112.f;
	float sliceWidth = 192.f;
	Vec2 offset = { 0.f, -25.f };

	GetComponent<Animator>()->CreateAnimation(L"IdleRight", _m_pTex, Vec2(0.f, 0.f),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 15, 0.1f, false, _animScale, offset);
	GetComponent<Animator>()->CreateAnimation(L"IdleLeft", _leftTex, Vec2(sliceWidth * 14, 0.f),
		Vec2(sliceWidth, sliceHeight), Vec2(-sliceWidth, 0.f), 15, 0.1f, false, _animScale, offset);

	GetComponent<Animator>()->CreateAnimation(L"MoveRight", _m_pTex, Vec2(0.f, sliceHeight * 2),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 6, 0.1f, false, _animScale, offset);
	GetComponent<Animator>()->CreateAnimation(L"MoveLeft", _leftTex, Vec2(sliceWidth * 14, sliceHeight * 2),
		Vec2(sliceWidth, sliceHeight), Vec2(-sliceWidth, 0.f), 6, 0.1f, false, _animScale, offset);

	GetComponent<Animator>()->CreateAnimation(L"AttackRight", _m_pTex, Vec2(0.f, sliceHeight * 3),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 3, 0.1f, false, _animScale, offset);
	GetComponent<Animator>()->CreateAnimation(L"AttackLeft", _leftTex, Vec2(sliceWidth * 14, sliceHeight * 3),
		Vec2(sliceWidth, sliceHeight), Vec2(-sliceWidth, 0.f), 3, 0.1f, false, _animScale, offset);

	GetComponent<Animator>()->CreateAnimation(L"DamagedRight", _m_pTex, Vec2(0.f, sliceHeight * 5),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 5, 0.1f, false, _animScale, offset);
	GetComponent<Animator>()->CreateAnimation(L"DamagedLeft", _leftTex, Vec2(sliceWidth * 14, sliceHeight * 5),
		Vec2(sliceWidth, sliceHeight), Vec2(-sliceWidth, 0.f), 5, 0.1f, false, _animScale, offset);

	GetComponent<Animator>()->CreateAnimation(L"DeadRight", _m_pTex, Vec2(0.f, sliceHeight * 6),
		Vec2(sliceWidth, sliceHeight), Vec2(sliceWidth, 0.f), 11, 0.1f, false, _animScale, offset);
	GetComponent<Animator>()->CreateAnimation(L"DeadLeft", _leftTex, Vec2(sliceWidth * 14, sliceHeight * 6),
		Vec2(sliceWidth, sliceHeight), Vec2(-sliceWidth, 0.f), 11, 0.1f, false, _animScale, offset);

	SetSize(Vec2(192.f, 112.f));

	BossMovePointInit();

	GetComponent<Animator>()->PlayAnimation(L"IdleRight", true);
	GetComponent<Collider>()->SetSize(Vec2(192.f / 2, 112.f));
}

void Stage2Boss::Render(HDC _hdc)	
{
	ComponentRender(_hdc);
}

void Stage2Boss::PatternInit()
{
	RandomLaserPattern* randomLaser = new RandomLaserPattern();
	AddPattern<Stage2BossPattern>(Stage2BossPattern::RandomLaser, randomLaser);

	LeftFullLaserPattern* leftFullLaser = new LeftFullLaserPattern();
	AddPattern<Stage2BossPattern>(Stage2BossPattern::LeftFullLaser, leftFullLaser);

	RightFullLaserPattern* rightFullLaser = new RightFullLaserPattern();
	AddPattern<Stage2BossPattern>(Stage2BossPattern::RightFullLaser, rightFullLaser);

	CenterFullLaserPattern* centerFullLaser = new CenterFullLaserPattern();
	AddPattern<Stage2BossPattern>(Stage2BossPattern::CenterFullLaser, centerFullLaser);

	ZigzagLaserPattern* zigzagLaser = new ZigzagLaserPattern();
	AddPattern<Stage2BossPattern>(Stage2BossPattern::ZigzagLaser, zigzagLaser);

	ZigzagRandomLaserPattern* zigzagRandomLaser = new ZigzagRandomLaserPattern();
	AddPattern<Stage2BossPattern>(Stage2BossPattern::ZigzagRandomLaser, zigzagRandomLaser);

	for (auto iter = _bossPattern.begin(); iter != _bossPattern.end(); iter++)
	{
		iter->second->Init(this);
	}
}

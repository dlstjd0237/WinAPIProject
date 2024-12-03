#include "pch.h"
#include "Player.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Projectile.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Animator.h"
#include "Animation.h"
#include "RigidBody.h"

Player::Player()
	: m_pTex(nullptr),
	m_speed(10)
{

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\Warrior.bmp");

	//==== AddComponent ====
	this->AddComponent<RigidBody>();
	this->AddComponent<Collider>();
	this->AddComponent<Animator>();
	//======================

	//==== Graviy Setting ====
	SetUseGravity(true);
	//========================

	//==== Animation Setting ====
	GetComponent<Animator>()->CreateAnimation(L"PlayerRightMove", m_pTex, Vec2(0.f, 44.f),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, false, 4);
	GetComponent<Animator>()->CreateAnimation(L"PlayerLeftMove", m_pTex, Vec2(0.f, 44.f),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, true, 4);
	GetComponent<Animator>()->CreateAnimation(L"PlayerRightIdle", m_pTex, Vec2(0.f, 0.f),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, false, 4);
	GetComponent<Animator>()->CreateAnimation(L"PlayerLeftIdle", m_pTex, Vec2(0.f, 0.f),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, true, 4);
	//GetComponent<Animator>()->CreateAnimation(L"JiwooBack", m_pTex, Vec2(0.f, 200.f),
	//	Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"PlayerRightIdle", true);
	//============================


	//==== Collider Setting =====
	GetComponent<Collider>()->SetSize({ 69.f * 2 - 15, 44.f * 3 });
	GetComponent<Collider>()->SetOffSetPos({ -32, 19 });
	//===========================
}
Player::~Player()
{
	//if (nullptr != m_pTex)
	//	delete m_pTex;
}
void Player::Update()
{
	UseGravity();
	Vec2 vPos = GetPos();


	if (GET_KEY(KEY_TYPE::A)) {
		vPos.x -= 100.f * fDT * m_speed;
		SetEnergy(m_energy += 0.001f);
	}
	if (GET_KEYDOWN(KEY_TYPE::A)) {
		AnimationChange(PLAYER_ANIM_TYPE::MOVE, true);
	}
	if (GET_KEYUP(KEY_TYPE::A)) {
		AnimationChange(PLAYER_ANIM_TYPE::IDLE, true);
	}

	if (GET_KEY(KEY_TYPE::D)) {
		vPos.x += 100.f * fDT * m_speed;
		SetEnergy(m_energy += 0.001f);
	}
	if (GET_KEYDOWN(KEY_TYPE::D)) {
		AnimationChange(PLAYER_ANIM_TYPE::MOVE);
	}
	if (GET_KEYUP(KEY_TYPE::D)) {
		AnimationChange(PLAYER_ANIM_TYPE::IDLE);
	}
	if (m_isJumping) {
		// �ӵ��� ���� ��ġ ��ȭ
		m_jumpVelocity += GetGravity() * fDT; // �߷� ���ӵ� ����
		vPos.y += m_jumpVelocity * fDT;
	}

	if (GET_KEYDOWN(KEY_TYPE::SPACE)) {

		Jump();
	}
	SetPos(vPos);
}

void Player::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	ComponentRender(_hdc);
	//::StretchBlt();
	//::AlphaBlend();
	//::PlgBlt();
}

void Player::EnterCollision(Collider* _other)
{

	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Ground")
	{
		SetUseGravity(false);
		m_isJumping = false;
		m_jumpVelocity = 0.f;
	}
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
}

void Player::CreateProjectile()
{
	Projectile* pProj = new Projectile;
	Vec2 vPos = GetPos();
	vPos.y -= GetSize().y / 2.f;
	pProj->SetPos(vPos);
	pProj->SetSize({ 30.f,30.f });

	pProj->SetDir({ 0.f, -1.f });
	pProj->SetName(L"PlayerBullet");
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}

void Player::Jump()
{
	if (!m_isJumping) // ���� ���� �ƴ� ���� ����
	{
		SetUseGravity(true);
		m_isJumping = true;
		m_jumpVelocity = -500.f * m_energy; // ���� �ö󰡴� �ʱ� �ӵ� (px/s)
		SetEnergy(1);
	}

}

void Player::AnimationChange(PLAYER_ANIM_TYPE animType, bool Flip)
{
	switch (animType)
	{
	case PLAYER_ANIM_TYPE::IDLE:
		if(Flip)
		GetComponent<Animator>()->PlayAnimation(L"PlayerRightIdle", true);
		else
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftIdle", true);
		
		break;
	case PLAYER_ANIM_TYPE::MOVE:
		if (Flip == true)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightMove", true);
		else
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftMove", true);
		break;
	case PLAYER_ANIM_TYPE::JUMP:
		m_isJumping = true;
		break;
	}
}

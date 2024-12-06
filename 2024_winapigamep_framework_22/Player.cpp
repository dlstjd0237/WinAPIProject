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
#include "PlayerAttackEffect.h"
#include "EntityManager.h"

Player::Player()
	: m_pTex(nullptr),
	m_speed(10)
{

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\Warrior.bmp");
	GET_SINGLE(EntityManager)->SetPlayer(this);

	//==== AddComponent ====
	this->AddComponent<Collider>();
	this->AddComponent<Animator>();
	//======================

	//==== Graviy Setting ====
	SetUseGravity(true);
	//========================

	//==== Animation Setting ====
	float scale = GetPlayerScale();
	GetComponent<Animator>()->CreateAnimation(L"PlayerRightAttack", m_pTex, Vec2(0.f, 44.0f * 13),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 4, 0.1f, false, scale);
	GetComponent<Animator>()->CreateAnimation(L"PlayerLeftAttack", m_pTex, Vec2(0.f, 44.0f * 30),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 4, 0.1f, true, scale);
	//============================
	// 
	//==== Jump Animtion ====
	GetComponent<Animator>()->CreateAnimation(L"PlayerRightJump", m_pTex, Vec2(0.f, 44.0f * 7),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, false, scale);
	GetComponent<Animator>()->CreateAnimation(L"PlayerLeftJump", m_pTex, Vec2(0.f, 44.0f * 24),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, true, scale);
	//=======================
	//
	//==== Move Animation ====
	GetComponent<Animator>()->CreateAnimation(L"PlayerRightMove", m_pTex, Vec2(0.f, 44.f),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, false, scale);
	GetComponent<Animator>()->CreateAnimation(L"PlayerLeftMove", m_pTex, Vec2(0.f, 44.f * 18.0f),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, true, scale);
	//========================
	//
	//==== Idle Animation ====
	GetComponent<Animator>()->CreateAnimation(L"PlayerRightIdle", m_pTex, Vec2(0.f, 0.f),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, false, scale);
	GetComponent<Animator>()->CreateAnimation(L"PlayerLeftIdle", m_pTex, Vec2(0.f, 44.f * 17),
		Vec2(69.f, 44.f), Vec2(69.f, 0.f), 6, 0.1f, true, scale);
	//=========================
	//
	//==== Animation play ====
	GetComponent<Animator>()->PlayAnimation(L"PlayerRightIdle", true);
	//========================
	//
	//==== Animation Setting End ====


}

Player::~Player()
{
	GET_SINGLE(EntityManager)->SetPlayer(nullptr);
}

void Player::Update()
{
	UseGravity();
	Vec2 vPos = GetPos();
	bool vFlip = m_isFlip;

	float x = vPos.x;
	float y = vPos.y;

	//==== Axis ====
	if (GET_KEY(KEY_TYPE::A) && m_isLeftWallDetected == false) {
		vPos.x -= 100.f * fDT * m_speed;
		SetEnergy(m_energy + 0.005f);
		m_isMoveing = true;
	}
	//==============
	if (GET_KEY(KEY_TYPE::D) && m_isRightWallDetected == false) {
		vPos.x += 100.f * fDT * m_speed;
		SetEnergy(m_energy + 0.005f);
		m_isMoveing = true;
	}
	//==============


	//==== Jump ====
	if (m_isJumping) {
		m_jumpVelocity += GetGravity() * fDT; // �߷¿� ���� �ӵ� ��ȭ
		vPos.y += m_jumpVelocity * fDT; // ���� ���� ��� ��ġ ���
	}

	if (GET_KEYDOWN(KEY_TYPE::SPACE) && m_isJumping == false && m_isGround == true) {
		Jump();
	}
	//==============

	if (GET_KEYDOWN(KEY_TYPE::LBUTTON) && m_isAttackTrigger == false)
	{
		m_isAttackTrigger = true;
	}

	SetPos(vPos);
	if (x != vPos.x)
		m_isFlip = x > vPos.x ? false : true;

	if (m_actionMap[PLAYER_ANIM_TYPE::ATTACK] == false && m_isAttackTrigger == true)
	{
		AnimationChange(PLAYER_ANIM_TYPE::ATTACK, m_isFlip);
		ActionMapChange(PLAYER_ANIM_TYPE::ATTACK);
	}
	else if (x == vPos.x && m_actionMap[PLAYER_ANIM_TYPE::IDLE] == false
		&& m_isJumping == false && m_isAttackTrigger == false)
	{
		m_isFlip = vFlip;
		AnimationChange(PLAYER_ANIM_TYPE::IDLE, vFlip);
		ActionMapChange(PLAYER_ANIM_TYPE::IDLE);
	}
	else if (vFlip != m_isFlip || (x != vPos.x && m_actionMap[PLAYER_ANIM_TYPE::MOVE] == false
		&& m_isJumping == false && m_isAttackTrigger == false))
	{
		m_isFlip = x > vPos.x ? false : true;
		AnimationChange(PLAYER_ANIM_TYPE::MOVE, m_isFlip);
		ActionMapChange(PLAYER_ANIM_TYPE::MOVE);
	}
	else if (y != vPos.y && m_actionMap[PLAYER_ANIM_TYPE::JUMP] == false
		&& m_isAttackTrigger == false)
	{
		AnimationChange(PLAYER_ANIM_TYPE::JUMP, m_isFlip);

		ActionMapChange(PLAYER_ANIM_TYPE::JUMP);
	}

	if (m_isAttackTrigger)
	{
		m_attackTimer += fDT;
		if (m_attackTimer >= m_attackDelay)
		{
			PerformAttack(); // 0.6�� �� ����
		}
	}
}




void Player::Render(HDC _hdc)
{
	ComponentRender(_hdc);
}

void Player::EnterCollision(Collider* _other)
{

	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Ground")
	{
		m_isJumping = false; // ���� ����
		SetUseGravity(false); // �ٽ� �߷� Ȱ��ȭ
		m_isGround = true;
		m_isJumping = false;
		m_jumpVelocity = 0.f;
	}

	if (pOtherObj->GetName() == L"LeftWall") {
		m_isLeftWallDetected = true;
	}

	if (pOtherObj->GetName() == L"RightWall") {
		m_isRightWallDetected = true;
	}
}

void Player::StayCollision(Collider* _other)
{
}

void Player::ExitCollision(Collider* _other)
{
	Object* pOtherObj = _other->GetOwner();
	if (pOtherObj->GetName() == L"Ground")
		m_isGround = false;


	if (pOtherObj->GetName() == L"LeftWall") {
		m_isLeftWallDetected = false;
	}

	if (pOtherObj->GetName() == L"RightWall") {
		m_isRightWallDetected = false;
	}
}

// ���� ����Ʈ ����
void Player::CreateAttackEffect()
{
	PlayerAttackEffect* pEffect = new PlayerAttackEffect(this, m_isFlip);
	pEffect->SetSize({ 150.f, 150.f });

	pEffect->SetName(L"PlayerAttackEffect");
	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pEffect, LAYER::ATTACKEFFECT);

}


void Player::Jump()
{
	if (!m_isJumping) // ���� ���� �ƴ� ���� ����
	{
		m_isJumping = true;
		SetUseGravity(true);
		m_jumpVelocity = -300 * m_energy; // ���� �ö󰡴� �ʱ� �ӵ� (px/s)
	}
}

void Player::PerformAttack()
{
	SetEnergy(1);

	GET_SINGLE(ResourceManager)->LoadSound(L"swing", L"Sound\\swing1.wav", false);
	GET_SINGLE(ResourceManager)->Play(L"swing");

	m_isAttackTrigger = false; // Attack ���� ����
	m_attackTimer = 0;
	m_actionMap[PLAYER_ANIM_TYPE::ATTACK] = false;
}

void Player::AnimationChange(PLAYER_ANIM_TYPE animType, bool Flip)
{
	switch (animType)
	{
	case PLAYER_ANIM_TYPE::IDLE:
		if (Flip)
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
		if (Flip == true)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightJump", true);
		else
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftJump", true);
		m_isJumping = true;
		break;
	case PLAYER_ANIM_TYPE::ATTACK:
		if (Flip == true)
			GetComponent<Animator>()->PlayAnimation(L"PlayerRightAttack", false);
		else
			GetComponent<Animator>()->PlayAnimation(L"PlayerLeftAttack", false);


		//�̰����� ����Ʈ ����
		CreateAttackEffect();
		break;
	}


	if (Flip == true)
	{
		GetComponent<Collider>()->SetSize(GetSize());
		GetComponent<Collider>()->SetOffSetPos({ -16, 9 });
	}
	else {
		GetComponent<Collider>()->SetSize(GetSize());
		GetComponent<Collider>()->SetOffSetPos({ 16, 9 });
	}


}



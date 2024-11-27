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
	//m_pTex = new Texture;
	//wstring path = GET_SINGLE(ResourceManager)->GetResPath();
	//path += L"Texture\\planem.bmp";
	//m_pTex->Load(path);
	//m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Player", L"Texture\\planem.bmp");
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Jiwoo", L"Texture\\jiwoo.bmp");
	this->AddComponent<RigidBody>();
	this->AddComponent<Collider>();
	this->AddComponent<Animator>();

	SetUseGravity(true);

	GetComponent<Animator>()->CreateAnimation(L"JiwooFront", m_pTex, Vec2(0.f, 150.f),
		Vec2(50.f, 50.f), Vec2(50.f, 0.f), 5, 0.1f);
	GetComponent<Animator>()->PlayAnimation(L"JiwooFront", true);


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
	}

	if (GET_KEY(KEY_TYPE::D)) {
		vPos.x += 100.f * fDT * m_speed;
	}

	if (m_isJumping) {
		// ¼Óµµ¿¡ µû¸¥ À§Ä¡ º¯È­
		m_jumpVelocity += GetGravity() * fDT; // Áß·Â °¡¼Óµµ Àû¿ë
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
	//RECT_RENDER(_hdc, vPos.x, vPos.y
	//	, vSize.x, vSize.y);
	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	//::BitBlt(_hdc
	//	, (int)(vPos.x - vSize.x / 2)
	//	, (int)(vPos.y - vSize.y / 2)
	//	, width, height,
	//	m_pTex->GetTexDC()
	//	,0,0,SRCCOPY
	//);
	/*::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,
		m_pTex->GetTexDC()
		, 0, 0,width, height, RGB(255,0,255));*/
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
<<<<<<< HEAD
	pProj->SetSize({ 30.f,30.f });
=======
	pProj->SetSize({30.f,30.f});
	// ï¿½ï¿½ -> ï¿½ï¿½ï¿½ï¿½: PI / 180
	//pProj->SetAngle(PI / 4 * 7.f); // 1
>>>>>>> Realion033
	//static float angle = 0.f;
	//pProj->SetAngle(angle * PI / 180); // 2
	//angle += 10.f;
	pProj->SetDir({ 0.f, -1.f });
	pProj->SetName(L"PlayerBullet");
	//Vec2 a = { 10.f, 10.f };
	//Vec2 b = { 0.f, 0.f };
	//Vec2 c = a / b;

	GET_SINGLE(SceneManager)->GetCurrentScene()->AddObject(pProj, LAYER::PROJECTILE);
}

void Player::Jump()
{
	if (!m_isJumping) // Á¡ÇÁ ÁßÀÌ ¾Æ´Ò ¶§¸¸ °¡´É
	{
		SetUseGravity(true);
		m_isJumping = true;
		m_jumpVelocity = -500.f; // À§·Î ¿Ã¶ó°¡´Â ÃÊ±â ¼Óµµ (px/s)
	}

}

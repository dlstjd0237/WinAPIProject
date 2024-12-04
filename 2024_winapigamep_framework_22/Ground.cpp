#include "pch.h"
#include "Ground.h"
#include "Collider.h"
#include "Texture.h"
#include "ResourceManager.h"

Ground::Ground()
	:m_pTex(nullptr)
{
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Ground", L"Texture\\ground.bmp");
	this->AddComponent<Collider>();

	GetComponent<Collider>()->SetSize(Vec2(1920, 50));
	GetComponent<Collider>()->SetOffSetPos(Vec2(0, 280));

}

Ground::~Ground()
{
}

void Ground::Update()
{
}

void Ground::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();


	::TransparentBlt(_hdc
		, (int)(vPos.x - width / 2)
		, (int)(vPos.y - height / 2)
		, width, height,  // 출력 크기를 두 배로
		m_pTex->GetTexDC()
		, 0, 0, width, height,       // 원본 크기는 그대로
		RGB(255, 0, 255));
	ComponentRender(_hdc);
}

void Ground::EnterCollision(Collider* _other)
{

}

void Ground::StayCollision(Collider* _other)
{
}

void Ground::ExitCollision(Collider* _other)
{
}

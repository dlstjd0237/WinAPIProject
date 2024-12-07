#include "pch.h"
#include "Ground.h"
#include "Collider.h"
#include "Texture.h"
#include "ResourceManager.h"

Ground::Ground(bool _useTextur, Vec2 _colliderSize, Vec2 _colliderOffSet)
	:m_pTex(nullptr)
	, m_useTexur(_useTextur)
{
	if (_useTextur)
		m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(L"Ground", L"Texture\\ground.bmp");

	this->AddComponent<Collider>();

	GetComponent<Collider>()->SetSize(_colliderSize);
	GetComponent<Collider>()->SetOffSetPos(_colliderOffSet);

}

Ground::~Ground()
{
}

void Ground::Update()
{
}

void Ground::Render(HDC _hdc)
{
	if (m_useTexur == false) {
		ComponentRender(_hdc);
		return;
	}
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

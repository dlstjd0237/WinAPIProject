#include "pch.h"
#include "Ground.h"
#include "Collider.h"

Ground::Ground()
{
	this->AddComponent<Collider>();

	GetComponent<Collider>()->SetSize(Vec2(1920, 50));
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
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);
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

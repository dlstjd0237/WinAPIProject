#include "pch.h"
#include "Background.h"
#include "ResourceManager.h"
#include "Texture.h"


Background::Background(wstring _texturName, wstring _texturePath,
	Vec2 _scale, Object* _player, float _offset) :
	m_pTex(nullptr)
	, m_scale(_scale)
	, m_texturName(_texturName)
	, m_texturPath(_texturePath)
	, m_pOnwer(_player)
	, m_offset(_offset)
{
	m_prevOwnerPos = _player->GetPos();
	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(m_texturName, m_texturPath);
}

Background::~Background()
{
}

void Background::Update()
{
	Vec2 currPlayerPos = m_pOnwer->GetPos();

	Vec2 delta = currPlayerPos - m_prevOwnerPos;

	Vec2 groundPos = GetPos();
	
	groundPos.x -= delta.x * m_offset;

	SetPos(groundPos);

	m_prevOwnerPos = currPlayerPos;
}

void Background::Render(HDC _hdc)
{
	Vec2 vPos = GetPos();

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();
	int scaledWidth = width * m_scale.x;
	int scaledHeight = height * m_scale.y;

	::TransparentBlt(_hdc
		, (int)(vPos.x - scaledWidth / 2)
		, (int)(vPos.y - scaledHeight / 2)
		, scaledWidth, scaledHeight,  // ��� ũ�⸦ �� ���
		m_pTex->GetTexDC()
		, 0, 0, width, height,       // ���� ũ��� �״��
		RGB(255, 0, 255));
	ComponentRender(_hdc);
}

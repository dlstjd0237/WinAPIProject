#include "pch.h"
#include "Background.h"
#include "ResourceManager.h"
#include "Texture.h"


Background::Background(wstring _texturName, wstring _texturePath,
	Object* _player, float _offset) :
	m_pTex(nullptr)

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
	if (m_prevOwnerPos.x == currPlayerPos.x || m_offset == 0)
		return;

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

	if (m_offset == 0) {
		BitBlt(_hdc
			, (int)(vPos.x - width / 2)
			, (int)(vPos.y - height / 2)
			, width, height  // ������ ��ŭ
			, m_pTex->GetTexDC()
			, 0, 0, SRCCOPY);
	}
	else {
		::TransparentBlt(_hdc
			, (int)(vPos.x - width / 2)
			, (int)(vPos.y - height / 2)
			, width, height,  // ������ ��ŭ 
			m_pTex->GetTexDC()
			, 0, 0, width, height,       // ���� ũ��� �״��
			RGB(255, 0, 255));
	}
}

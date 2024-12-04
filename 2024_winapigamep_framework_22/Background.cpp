#include "pch.h"
#include "Background.h"
#include "ResourceManager.h"
#include "Texture.h"


Background::Background(wstring _texturName, wstring _texturePath, Vec2 _scale) :
	m_pTex(nullptr)
	, m_scale(_scale)
	, m_texturName(_texturName)
	, m_texturPath(_texturePath)
{

	m_pTex = GET_SINGLE(ResourceManager)->TextureLoad(m_texturName, m_texturPath);

}

Background::~Background()
{
}

void Background::Update()
{
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
		, scaledWidth, scaledHeight,  // 출력 크기를 두 배로
		m_pTex->GetTexDC()
		, 0, 0, width, height,       // 원본 크기는 그대로
		RGB(255, 0, 255));
	ComponentRender(_hdc);
}

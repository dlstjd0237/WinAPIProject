#pragma once
#include "Object.h"

class Texture;
class Background :
	public Object
{

public:
	Background(wstring _texturName, wstring _texturePath,
		Vec2 _scale, Object* _player, float _offset);
	~Background();

public:
	void Update() override;
	void Render(HDC _hdc) override;

private:
	Texture* m_pTex;
	Object* m_pOnwer;
	wstring m_texturPath;
	wstring m_texturName;
	Vec2  m_scale;
	Vec2 m_prevOwnerPos;
	float	 m_offset;
public:
	const Vec2 GetScale()const { return m_scale; }
	void SetScale(Vec2 _scale) { m_scale = _scale; }
};


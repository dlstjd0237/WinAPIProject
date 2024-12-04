#pragma once
#include "Object.h"

class Texture;
class Background :
	public Object
{

public:
	Background(wstring _texturName, wstring _texturePath,
		Object* _player, float _offset);
	~Background();

public:
	void Update() override;
	void Render(HDC _hdc) override;

private:
	Texture* m_pTex;
	Object* m_pOnwer;
	wstring m_texturPath;
	wstring m_texturName;
	Vec2 m_prevOwnerPos;
	float	 m_offset;

};


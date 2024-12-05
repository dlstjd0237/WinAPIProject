#pragma once
#include "Object.h"
#include "Texture.h"
#include <string>;
#include <functional>

class UI_Button : public Object
{
public:
	UI_Button( std::wstring bgPath,  std::wstring text, Vec2 _scale, std::wstring _name);
	~UI_Button();
	std::function<void()> OnClick;
public:
	// Object을(를) 통해 상속됨
	void Update() override;
	void Render(HDC _hdc) override;

private:
	Vec2 m_scale;
	Texture* m_pBgTex;
	wstring m_text;
	wstring m_texturPath;
	wstring m_texturName;

public:
	const Vec2 GetScale()const { return m_scale; }
	void SetScale(Vec2 _scale) { m_scale = _scale; }
};
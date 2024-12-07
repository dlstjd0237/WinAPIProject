#pragma once
#include "Object.h"
#include "Texture.h"
#include <string>
#include <functional>

class UI_Button : public Object
{
public:
	UI_Button(std::wstring bgPath, std::wstring text, Vec2 _scale, std::wstring _name, Vec2 textScale, bool _isoutline);
	~UI_Button();
	std::function<void()> OnClick;

public:
	void Update() override;
	void Render(HDC _hdc) override;

private:
	Vec2 m_scale;
	Vec2 m_textScale;
	Texture* m_pBgTex;
	wstring m_text;
	wstring m_texturPath;
	wstring m_texturName;
	bool isOutLine;
	bool isMouseOverOutline;

public:
	const Vec2 GetScale()const { return m_scale; }
	void SetScale(Vec2 _scale) { m_scale = _scale; }
};
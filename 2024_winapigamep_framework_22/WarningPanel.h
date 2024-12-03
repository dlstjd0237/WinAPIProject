#pragma once
#include "Object.h"
class WarningPanel : public Object
{
public:
	WarningPanel(float fadeTime, Vec2 pos, Vec2 size);
private:
	void Update() override;
	void Render(HDC _hdc) override;
public:
	bool isFade;
private:
	float _fadeTime;
	float _deltaTime;
	float _fadeValue;
	BLENDFUNCTION bf;
};


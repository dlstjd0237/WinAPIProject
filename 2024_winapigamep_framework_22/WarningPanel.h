#pragma once
#include "Object.h"
class WarningPanel : public Object
{
public:
	WarningPanel(float fadeTime, Vec2 pos, Vec2 size, bool isCenter);
	~WarningPanel();
private:
	void Update() override;
	void Render(HDC _hdc) override;
	void RotateBlt(HDC _hdc);
	void DCInit(HDC hdc, int width, int height);
	void DCRealase();
public:
	void SetRotate(Vec2 dir) { _angle = atan2(dir.y, dir.x); }
public:
	bool isRotate;
	bool isFade;
private:
	float _angle;
	float _fadeTime;
	float _deltaTime;
	float _fadeValue;
	BLENDFUNCTION bf;
	HDC alphaDC;
	HBITMAP alphaBit;
	HDC rotateDC;
	HBITMAP rotateBit;
};


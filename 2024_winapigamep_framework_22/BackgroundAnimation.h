#pragma once
#include "Object.h"
class Texture;
class BackgroundAnimation : public Object
{
public:
	BackgroundAnimation(wstring _texturPath,int _fram,
		Vec2 _texturSliceSize,  float _scale);
	~BackgroundAnimation();


public:
	void Update() override;
	void Render(HDC _hdc) override;

private:
	Texture* m_pTex;
};


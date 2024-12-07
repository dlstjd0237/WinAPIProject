#pragma once
#include "Object.h"
class LoadingPanel : public Object
{
public:
	void Load(bool isFadeIn, float time);
	void Update() override;
	void Render(HDC _hdc) override;
private:
	float _deltaTime;
	float _fadeTime;
	bool _isFadeIn;
public:
	bool isComplete;
	bool isLoading;
};


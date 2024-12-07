#pragma once
#include "Object.h"
class LoadingPanel : public Object
{
public:
	void Load(bool isFadeIn, float time, float delay = 0.f);
	void Update() override;
	void Render(HDC _hdc) override;
private:
	float _deltaTime;
	float _delayDeltaTime;
	float _fadeTime;
	float _delayTime;
public:
	bool isFadeIn;
	bool isComplete;
	bool isLoading;
};


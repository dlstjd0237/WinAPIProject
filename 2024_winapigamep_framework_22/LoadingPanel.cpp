#include "pch.h"
#include "LoadingPanel.h"
#include "GDISelector.h"
#include "TimeManager.h"

void LoadingPanel::Load(bool isFadeIn, float time , float delay)
{
	_delayTime = delay;
	isLoading = true;
	isComplete = false;
	this->isFadeIn = isFadeIn;
	_fadeTime = time;
	_delayDeltaTime = 0.f;
}

void LoadingPanel::Update()
{
	if (isLoading)
	{
		if (_delayDeltaTime <= _delayTime)
		{
			_delayDeltaTime += fDT;
			return;
		}

		_deltaTime += fDT;
		float elapseTime = _deltaTime / _fadeTime;
		float x = 0;
		if (isFadeIn)
			x = std::lerp(-SCREEN_WIDTH / 2.f, SCREEN_WIDTH / 2.f, elapseTime);
		else
			x = std::lerp(SCREEN_WIDTH / 2.f, -SCREEN_WIDTH / 2.f, elapseTime);
		SetPos({ x, SCREEN_HEIGHT / 2.f });
		if (elapseTime >= 1)
		{
			isLoading = false;
			isComplete = true;
		}
	}
}

void LoadingPanel::Render(HDC _hdc)
{
	HBRUSH brush = CreateSolidBrush(RGB(0,0,0));
	HBRUSH oldbrush = (HBRUSH)SelectObject(_hdc, brush);
	Vec2 vPos = GetPos();
	Vec2 vSize = GetSize();
	RECT_RENDER(_hdc, vPos.x, vPos.y
		, vSize.x, vSize.y);
	SelectObject(_hdc, oldbrush); 
	DeleteObject(brush);
}

#include "pch.h"
#include "CameraManager.h"
#include "TimeManager.h"

void CameraManager::Init()
{
	_isShaking = false;
	_camOffset = { 0,0 };
}

void CameraManager::Update()
{
	if (_isShaking)
	{
		_deltaTime += fDT;

		_camOffset.x = (rand() % _power + 1) - _power;
		_camOffset.y = (rand() % _power + 1) - _power;

		if (_deltaTime >= _shakeTime)
		{
			_isShaking = false;
			_camOffset = { 0,0 };
			_deltaTime = 0.f;
		}
	}
}

void CameraManager::Shake(int power, float duration)
{
	_shakeTime = duration;
	_power = power;
	_isShaking = true;
	_deltaTime = 0.f;
}

#pragma once
class CameraManager
{
	DECLARE_SINGLE(CameraManager);

public:
	void Init();
	void Update();
	void Shake(int power, float duration);
	const Vec2& GetOffset() { return _camOffset; }
private:
	bool _isShaking;
	Vec2 _camOffset;
	float _shakeTime;
	float _deltaTime;
	int _power;
};


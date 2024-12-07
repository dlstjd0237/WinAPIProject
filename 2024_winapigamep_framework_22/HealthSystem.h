#pragma once
#include "UI_Health.h"

class Object;
class HealthSystem
{
public:
	HealthSystem(float maxHealth, Object* owner, UI_Health* bar);
public:
	void OnDamage(float damage);
	void OnRecovery();
	void SetCurrentHealth(float _value);
private:
	Object* _owner;
	float _currentHealth;
	float _maxHealth;
	UI_Health* _bar;
};

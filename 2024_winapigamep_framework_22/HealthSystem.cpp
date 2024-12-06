#include "pch.h"
#include "HealthSystem.h"

HealthSystem::HealthSystem(float maxHealth, Object* owner, UI_Health* bar)
{
	_maxHealth = maxHealth;
	_bar = bar;
	_owner = owner;
	_currentHealth = maxHealth;
}

void HealthSystem::OnDamage(float damage)
{
	_currentHealth -= damage;
	_bar->SetFillAmount(_currentHealth / _maxHealth);

	// SetDead 바로 실행시키면 다음 프레임 때 사라짐 (DeadAnimation 실행 불가)
	// DeadProcess에서 처리 후 SetDead하기
	if (_currentHealth <= 0)
	{
		_owner->DeadProcess();
	}
}

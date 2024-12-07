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

	// SetDead �ٷ� �����Ű�� ���� ������ �� ����� (DeadAnimation ���� �Ұ�)
	// DeadProcess���� ó�� �� SetDead�ϱ�
	if (_currentHealth <= 0)
	{
		_owner->DeadProcess();
	}
}

void HealthSystem::OnRecovery()
{
	_currentHealth = _maxHealth;
	_bar->SetFillAmount(_currentHealth / _maxHealth);
}

void HealthSystem::SetCurrentHealth(float _value)
{
	_currentHealth = _value;
	_bar->SetFillAmount(_currentHealth / _maxHealth);
}


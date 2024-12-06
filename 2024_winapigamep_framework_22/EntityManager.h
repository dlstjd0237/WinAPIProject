#pragma once
class Object;
class EntityManager
{
	DECLARE_SINGLE(EntityManager);

public:
	void Init();
private:
	Object* m_pPlayer = nullptr;
	Object* m_pBoss = nullptr;

public:
	const Object* GetPlayer() const { return  m_pPlayer; }
	const Object* GetBoss() const { return m_pBoss; }

	void SetPlayer(Object* _player) { m_pPlayer = _player; }
	void SetBoss(Object* _boss) { m_pPlayer = _boss; }

};


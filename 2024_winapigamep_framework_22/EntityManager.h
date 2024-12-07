#pragma once
class Object;
class Boss;
class Player;
class EntityManager
{
	DECLARE_SINGLE(EntityManager);

public:
	void Init();
private:
	Player* m_pPlayer = nullptr;
	Boss* m_pBoss = nullptr;

public:
	 Player* GetPlayer()  { return  m_pPlayer; }
	 Boss* GetBoss()  { return m_pBoss; }

	void SetPlayer(Player* _player) { m_pPlayer = _player; }
	void SetBoss(Boss* _boss) { m_pBoss = _boss; }

};
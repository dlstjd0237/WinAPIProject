#pragma once
class Object;
class Player;
class Boss;
class EntityManager
{
	DECLARE_SINGLE(EntityManager);

public:
	void Init();
private:
	Player* m_pPlayer = nullptr;
	Boss* m_pBoss = nullptr;

public:
	Player* GetPlayer() const { return  m_pPlayer; }
	Boss* GetBoss() const { return m_pBoss; }

	void SetPlayer(Player* _player) { m_pPlayer = _player; }
	void SetBoss(Boss* _boss) { m_pBoss = _boss; }

};
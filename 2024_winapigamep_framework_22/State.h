#pragma once

class AI;

class State
{
private:
	AI* m_pAI;
	STATE m_eState;

public:
	AI* GetAI() { return m_pAI; }

public:
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;

public:
	State(STATE _state);
	virtual ~State();

	friend class AI;
};


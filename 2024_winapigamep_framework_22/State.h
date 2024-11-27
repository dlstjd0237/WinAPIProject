#pragma once

class AI;

class State
{
private:
	AI* m_pAI;

public:
	AI* GetAI() { return m_pAI; }

public:
	State();
	virtual ~State();

	friend class AI;
};


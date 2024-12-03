#pragma once
#include "State.h"
class PlayerIdleState :
	public State
{
public :
	virtual void Enter();
	virtual void Update();
	virtual void Exit();
	

public:
	PlayerIdleState();
	~PlayerIdleState();
};


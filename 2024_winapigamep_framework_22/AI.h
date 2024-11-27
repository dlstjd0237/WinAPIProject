#pragma once

class Object;
class State;

class AI
{

private:
	map<STATE, State> m_mapState;
	Object* m_Owner;


public:
	AI();
	~AI();
};


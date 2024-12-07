#pragma once
#include "Scene.h"
class GameClearScene :
    public Scene
{
public:
	virtual void Init() override;
	void Release() override;
};


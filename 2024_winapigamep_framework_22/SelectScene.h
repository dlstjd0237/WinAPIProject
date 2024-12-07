#pragma once
#include "Scene.h"
class SelectScene :
    public Scene
{
    // Scene을(를) 통해 상속됨
    void Init() override;
    void Release() override;
};


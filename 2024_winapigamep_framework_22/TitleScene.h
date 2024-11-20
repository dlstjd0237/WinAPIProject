#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;

private:
    void UIInit(); // UI 초기화 멤버 함수
};
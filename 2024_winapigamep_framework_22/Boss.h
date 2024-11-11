#pragma once
#include <any>
#include "Object.h"

class BossPattern;
class Boss : public Object
{
public:
    Boss();
    virtual ~Boss();
public:
    void Update() override;
    void Render(HDC _hdc) override;
public:
    virtual void PatternInit() abstract;
protected:
    map<std::any, BossPattern*> bossPattern;
};
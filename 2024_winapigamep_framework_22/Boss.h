#pragma once
#include <any>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include "Object.h"

class BossPattern;

class Boss : public Object
{
public: 
    Boss();
    virtual ~Boss();
public:
    virtual void Update() override;
protected:
    virtual void PatternInit() abstract;
    int RandomPattenIdxGet(bool noDuplication);
    void PatternUpdate();

protected:
    template<typename T>
    void AddPattern(T patternEnum, BossPattern* pattern);

    template<typename T>
    BossPattern* GetPattern(T patternEnum);

    void PatternIdxInit();

protected:
    vector<int> _patternIdxVec;

    std::unordered_map<int, BossPattern*> _bossPattern;
    float _patternDelay;
    float _elapseTime;

    BossPattern* _currentPattern;
};

template<typename T>
inline void Boss::AddPattern(T patternEnum, BossPattern* pattern)
{
    int idx = static_cast<int>(patternEnum);
    _bossPattern[idx] = pattern;
}

template<typename T>
inline BossPattern* Boss::GetPattern(T patternEnum)
{
    int idx = static_cast<int>(patternEnum);
    if (_bossPattern.find(idx) != _bossPattern.end())
    {
        return _bossPattern[idx];
    }

    return NULL;
}

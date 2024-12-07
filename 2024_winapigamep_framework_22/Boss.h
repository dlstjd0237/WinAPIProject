#pragma once
#include "Object.h"
#include "ResourceManager.h"
#include "Animator.h"
#include "HealthSystem.h"

enum class Boss_ANIM_TYPE
{
    IDLE,
    MOVE,
    ATTACK,
    DAMAGED,
    DEAD
};

enum class BossMovePoint
{
    Left,
    LeftMiddle,
    Middle,
    RightMiddle,
    Right,
};


class BossPattern;
class Texture;
class Boss : public Object
{
public: 
    Boss();
    virtual ~Boss();
    void SetHealth(UI_Health* bar);

public:
    virtual void Update() override;
    void BossMoveInit(Vec2 targetPos, float moveTime);
    void AnimationChange(Boss_ANIM_TYPE anim, bool isFlip);
    void OnDamaged(int damage);
    void DeadProcess() override;

protected:
    virtual void PatternInit() abstract;
    int RandomPattenIdxGet(bool noDuplication);
    void PatternUpdate();
    void PatternIdxInit();
    void BossMovePointInit();
    void RandomBossMove();
    bool AnimationEndCheck();

private:
    void FlipCheck();
    void BossMove();

protected:
    template<typename T>
    void AddPattern(T patternEnum, BossPattern* pattern);
    template<typename T>
    BossPattern* GetPattern(T patternEnum);

protected:
    vector<int> _patternIdxVec;
    std::unordered_map<int, BossPattern*> _bossPattern;
    float _patternDelay;
    float _patternElapseTime;
    BossPattern* _currentPattern;
    
    float _moveTime;
    Vec2 _startPos;
    Vec2 _targetPos;
    float _moveDeltaTime;

    Texture* _m_pTex;
    Vec2 _animScale;
    Boss_ANIM_TYPE _currentAnimType = Boss_ANIM_TYPE::IDLE;
    Animation* _currentAnim;
    BossMovePoint _currentBossPoint;
    vector<Vec2> _movePointVec;
    HealthSystem* _health;

    bool _isDeading;
    bool _isDamaged;

private:
    int _addValue = 0;

public:
    bool isLeft;
    bool isMoving;
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
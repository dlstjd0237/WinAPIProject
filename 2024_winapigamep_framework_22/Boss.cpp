#include "pch.h"
#include "Boss.h"
#include "Stage1Boss.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Animator.h"

// ��� ���� �����ڿ��� PatternInit, PatternIdxInit ����� ��
Boss::Boss()
{
	AddComponent<Collider>();
	AddComponent<Animator>();
}

Boss::~Boss()
{

}

void Boss::Update()
{
	PatternUpdate();

	if (isMoving)
		BossMove();

	if (_currentPattern != NULL || isMoving)
		return;

	_patternElapseTime += fDT;

	if (_patternElapseTime >= _patternDelay)
	{
		_patternElapseTime = 0;

		// Debug
		_currentPattern = GetPattern<Stage1BossPattern>(Stage1BossPattern::SniperShot);
		// ���� ����
		//_currentPattern = GetPattern(RandomPattenIdxGet(true));
	}
}

void Boss::BossMoveInit(Vec2 targetPos, float moveTime)
{
	isMoving = true;
	_moveTime = moveTime;
	_targetPos = targetPos;
	_moveDeltaTime = 0;
	_startPos = GetPos();
	AnimationChange(Boss_ANIM_TYPE::MOVE, isLeft);
}

void Boss::FlipCheck()
{
	if (SCREEN_WIDTH / 2 <= GetPos().x)
	{
		if(!isLeft)
			AnimationChange(Boss_ANIM_TYPE::MOVE, !isLeft);
	}
	else
	{
		if (isLeft)
			AnimationChange(Boss_ANIM_TYPE::MOVE, !isLeft);
	}
}

void Boss::BossMove()
{
	_moveDeltaTime += fDT;
	float elapseTime = _moveDeltaTime / _moveTime;
	Vec2 pos = pos.VecLerp(_startPos, _targetPos, elapseTime);
	SetPos(pos);
	FlipCheck();

	if (elapseTime >= 1)
	{
		SetPos(_targetPos);
		AnimationChange(Boss_ANIM_TYPE::IDLE, isLeft);
		isMoving = false;
	}
}

void Boss::BossMovePointInit()
{
	Vec2 size = GetSize();
	float width = SCREEN_WIDTH / 4;

	// ���� ���
	_movePointVec.push_back({ size.x, size.y });
	for (int i = 1; i <= 3; i++)
	{
		_movePointVec.push_back({ width * i, size.y });
	}
	_movePointVec.push_back({ SCREEN_WIDTH - size.x, size.y });
}

void Boss::RandomBossMove()
{
	int randPoint = rand() % 5;
	if (randPoint == (int)_currentBossPoint)
		return;
	_currentBossPoint = (BossMovePoint)randPoint;
	BossMoveInit(_movePointVec[randPoint], 2.f);
}

int Boss::RandomPattenIdxGet(bool noDuplication)
{
	if (noDuplication == false || _addValue == _patternIdxVec.size())
		_addValue = 0;

	srand(unsigned int(time(NULL)));
	// ������ �ε����� ���� �� ��ų, �ߺ� ������ ���� ��� �������� ���� �������� ����
	int patIdx = rand() % (_patternIdxVec.size() - _addValue);

	// ������ �ε����� ���� ���� �ε����� ��ȯ
	int temp = _patternIdxVec[patIdx];
	_patternIdxVec[patIdx] = _patternIdxVec[_patternIdxVec.size() - 1 - _addValue];
	_patternIdxVec[_patternIdxVec.size() - 1 - _addValue] = temp;

	_addValue++;
	return temp;
}

void Boss::PatternUpdate()
{
	if (_currentPattern != NULL)
	{
		_currentPattern->Update();
		if (_currentPattern->isEnd)
		{
			_currentPattern->Exit();
			RandomBossMove();
			_currentPattern = NULL;
		}
	}
}

void Boss::PatternIdxInit()
{
	for (auto iter = _bossPattern.begin(); iter != _bossPattern.end(); iter++)
	{
		int i = (int)iter->first;
	    _patternIdxVec.push_back(i);
	}
}

void Boss::AnimationChange(Boss_ANIM_TYPE anim, bool isLeft)
{
	wstring key;
	bool isLoop;

	switch (anim)
	{
	case Boss_ANIM_TYPE::IDLE:
		key = L"Idle";
		isLoop = true;
		break;
	case Boss_ANIM_TYPE::MOVE:
		key = L"Move";
		isLoop = true;
		break;
	case Boss_ANIM_TYPE::ATTACK:
		key = L"Attack";
		break;
	case Boss_ANIM_TYPE::DAMAGED:
		key = L"Damaged";
		break;
	}

	if (isLeft)
		key += L"Left";
	else
		key += L"Right";

	this->isLeft = isLeft;
	GetComponent<Animator>()->PlayAnimation(key, isLoop);
}
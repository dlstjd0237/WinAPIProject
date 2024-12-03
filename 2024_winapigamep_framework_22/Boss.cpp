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

	if (_currentPattern != NULL)
		return;

	_patternElapseTime += fDT;

	if (_patternElapseTime >= _patternDelay)
	{
		_patternElapseTime = 0;

		//Debug
		//_currentPattern = GetPattern<Stage1BossPattern>(Stage1BossPattern::OneShot);
		// ���� ����
		_currentPattern = GetPattern(RandomPattenIdxGet(true));
	}
}

void Boss::BossMoveInit(Vec2 targetPos, float moveTime)
{
	isMoving = true;
	_moveTime = moveTime;
	_targetPos = targetPos;
	_moveDeltaTime = 0;
	_startPos = GetPos();
}

void Boss::BossMove()
{
	_moveDeltaTime += fDT;
	float elapseTime = _moveDeltaTime / _moveTime;
	Vec2 pos = pos.VecLerp(_startPos, _targetPos, elapseTime);
	SetPos(pos);

	if (elapseTime >= 1)
	{
		SetPos(_targetPos);
		isMoving = false;
	}
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
#include "pch.h"
#include "Boss.h"
#include "Stage1Boss.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Animator.h"

// 상속 받은 생성자에서 PatternInit, PatternIdxInit 해줘야 함
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
		// 랜덤 패턴
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
	// 마지막 인덱스는 전에 쓴 스킬, 중복 방지가 있을 경우 마지막을 빼고 랜덤에서 뽑음
	int patIdx = rand() % (_patternIdxVec.size() - _addValue);

	// 마지막 인덱스와 현재 랜덤 인덱스를 교환
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
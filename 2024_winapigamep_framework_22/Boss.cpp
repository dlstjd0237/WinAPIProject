#include "pch.h"
#include "Boss.h"
#include "Stage1Boss.h"
#include "TimeManager.h"

// 상속 받은 생성자에서 PatternInit, PatternIdxInit 해줘야 함
Boss::Boss()
{

}

Boss::~Boss()
{

}

void Boss::Update()
{
	PatternUpdate();

	if (_currentPattern != NULL)
		return;

	_elapseTime += GET_SINGLE(TimeManager)->GetDT();
	//cout << _elapseTime << endl;

	if (_elapseTime >= _patternDelay)
	{
		_elapseTime = 0;

		//Debug
		//_currentPattern = GetPattern<Stage1BossPattern>(Stage1BossPattern::OneShot);
		// 랜덤 패턴
		_currentPattern = GetPattern(RandomPattenIdxGet(true));
	}
}

int Boss::RandomPattenIdxGet(bool noDuplication)
{
	int addValue = 0;
	if (noDuplication)
		addValue = 1;

	srand(unsigned int(time(NULL)));
	// 마지막 인덱스는 전에 쓴 스킬, 중복 방지가 있을 경우 마지막을 빼고 랜덤에서 뽑음
	int patIdx = rand() % (_patternIdxVec.size() - addValue);

	// 마지막 인덱스와 현재 랜덤 인덱스를 교환
	int temp = _patternIdxVec[patIdx];
	_patternIdxVec[patIdx] = _patternIdxVec[_patternIdxVec.size() - 1];
	_patternIdxVec[_patternIdxVec.size() - 1] = temp;

	return _patternIdxVec[patIdx];
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

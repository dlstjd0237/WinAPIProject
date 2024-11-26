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
		_currentPattern = GetPattern<Stage1BossPattern>(Stage1BossPattern::OneShot);
		// 랜덤 패턴
		//_currentPattern = GetPattern(RandomPattenIdxGet(false));
	}
}

int Boss::RandomPattenIdxGet(bool noDuplication)
{
	int addValue = 0;
	if (noDuplication)
		addValue = 1;

	srand(unsigned int(time(NULL)));
	int patIdx = rand() % _patternIdxVec.size() - addValue;

	return patIdx;
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
		cout << i;
	    _patternIdxVec.push_back(i);
	}
}

#include "pch.h"
#include "Boss.h"
#include "Stage1Boss.h"
#include "TimeManager.h"

// ��� ���� �����ڿ��� PatternInit, PatternIdxInit ����� ��
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
		// ���� ����
		_currentPattern = GetPattern(RandomPattenIdxGet(true));
	}
}

int Boss::RandomPattenIdxGet(bool noDuplication)
{
	int addValue = 0;
	if (noDuplication)
		addValue = 1;

	srand(unsigned int(time(NULL)));
	// ������ �ε����� ���� �� ��ų, �ߺ� ������ ���� ��� �������� ���� �������� ����
	int patIdx = rand() % (_patternIdxVec.size() - addValue);

	// ������ �ε����� ���� ���� �ε����� ��ȯ
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

#pragma once

// ���� include
#include<Windows.h>
#include<tchar.h>
#include<memory>
#include<vector>
#include<list>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include<string>
#include<algorithm>
#include<ctime>
#define _USE_MATH_DEFINES
#include<math.h>

// My Header
#include "Define.h"
#include "Enums.h"
#include "Vec2.h"

// ���� lib
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib") // transparent �� blt�� ���
#pragma comment(lib, "fmod_vc.lib") 
#pragma comment(lib, "fmodL_vc.lib")

// ���� using
using std::vector;
using std::map;
using std::wstring;

// ���� define
#define PI 3.14159265f
#define SCREEN_WIDTH  1400	
#define SCREEN_HEIGHT 720

// ������ �ܼ�â
#ifdef _DEBUG
#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif
#include<iostream>
using std::cout;
using std::endl;

template <typename MapType>
void Safe_Delete_Map(MapType& map)
{
	for (auto& pair : map)
	{
		delete pair.second; //�޸𸮸� ����
		pair.second = nullptr; // nullptr�� �ʱ�ȭ
	}
	map.clear(); //�� ����
}
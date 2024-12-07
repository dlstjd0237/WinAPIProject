#include "pch.h"
#include "TimeManager.h"
#include "Core.h"
#include "InputManager.h"
void TimeManager::Init()
{
	// ī��Ʈ�� �����ؼ� �����´�.
	::QueryPerformanceCounter(&m_llPrevCnt);
	
	// �ʴ� ī��Ʈ Ƚ��(1�ʴ� 1000��) ��ȯ
	::QueryPerformanceFrequency(&m_llFrequency);
}

void TimeManager::Update()
{
	::QueryPerformanceCounter(&m_llCurCnt);
	
	//m_dT  = ;
	// deltatime(��ȭ�ð�) : �� �����ӿ� �ɸ� �ð� 
	m_dT = (float)(m_llCurCnt.QuadPart - m_llPrevCnt.QuadPart)
		/ (float)m_llFrequency.QuadPart;
	m_llPrevCnt = m_llCurCnt;

	// FPS(Frame Per Second): 1�ʴ� �� ������ ����.
	//1.f / m_dT;
	m_framecnt++; // ������ üũ Ƚ���� ���
	m_frametime += m_dT; // �����ð��� ���
	if (m_frametime >= 1.f) // 1��
	{
		m_fps = (UINT)(m_framecnt / m_frametime);
		m_frametime = 0.f;
		m_framecnt = 0;
		//wstring strfps = std::to_wstring(m_fps);
		//wstring strdt = std::to_wstring(m_dT);
		//wstring str = L"FPS : " + strfps  +
		//			 L" DT: " + strdt;
		//TextOut(GET_SINGLE(Core)->GetMainDC(),0,0, 
		//		str.c_str(),str.length());
		//std::format();
		//POINT mousepos = GET_SINGLE(InputManager)->GetMousePos();
		POINT mousepos = GET_MOUSEPOS;
		static wchar_t buf[100] = {};
		swprintf_s(buf, L"FPS: %d, DT: %f, Mouse: (%d, %d)",m_fps, m_dT
										,mousepos.x, mousepos.y);
		//::SetWindowText(GET_SINGLE(Core)->GetHwnd()
		//				, buf);
	}
}

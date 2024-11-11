#include "pch.h"
#include "InputManager.h"
#include "Core.h"
void InputManager::Init()
{
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		m_vecKey.push_back(tKeyInfo{KEY_STATE::NONE, false});
}

void InputManager::Update()
{

	//GetActiveWindow(); // â�� ������ ��ﶧ �� �����ִ� ������
	HWND hWnd = GetFocus(); // ���� �� ��Ŀ���Ѱ�
	if (hWnd == nullptr)
	{
		for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
		{
			m_vecKey[i].IsPrevCheck = false;
			m_vecKey[i].eState = KEY_STATE::NONE;
		}
		return;
	 }
	for (int i = 0; i < (int)KEY_TYPE::LAST; ++i)
	{
		// Ű�� ���ȴ�.
		if (GetAsyncKeyState(m_arrVKKey[i]))
		{
			// ������ ���Ⱦ�
			if (m_vecKey[i].IsPrevCheck)
				m_vecKey[i].eState = KEY_STATE::PRESS;
			else // ������ �ȴ��Ⱦ�. ���� ��!!! ����
				m_vecKey[i].eState = KEY_STATE::DOWN;
			m_vecKey[i].IsPrevCheck = true;
		}
		// Ű�� �ȴ��ȴ�.
		else
		{
			// ������ �����־���.
			if (m_vecKey[i].IsPrevCheck)
				m_vecKey[i].eState = KEY_STATE::UP;
			else
				m_vecKey[i].eState = KEY_STATE::NONE;
			m_vecKey[i].IsPrevCheck = false;
		}
	}
	// Mouse
	::GetCursorPos(&m_ptMouse); // ���콺 ��ǥ �ޱ�
	// �츮�� ���� ������ â �������� ��ǥ ����
	::ScreenToClient(GET_SINGLE(Core)->GetHwnd(), &m_ptMouse);


}

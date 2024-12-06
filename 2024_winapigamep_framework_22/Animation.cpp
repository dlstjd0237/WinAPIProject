#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Object.h"
#include "Texture.h"
#include "TimeManager.h"
#include "ResourceManager.h"

Animation::Animation()
	: m_pAnimator(nullptr)
	, m_CurFrame(0)
	, m_pTex(nullptr)
	, m_fAccTime(0.f)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_pAnimator->GetRepeatcnt() <= 0)
	{
		m_CurFrame = m_vecAnimFrame.size() - 1;
		return;
	}
	m_fAccTime += fDT;
	// ������ �ð��� ���� �� �����ӿ� ������ �ð��� �Ѿ��?
	if (m_fAccTime >= m_vecAnimFrame[m_CurFrame].fDuration)
	{
		// �ϴ� ���� �ð����� ���� ������ �ð��� ����
		m_fAccTime -= m_vecAnimFrame[m_CurFrame].fDuration;
		++m_CurFrame; // �������������� �ű��
		if (m_CurFrame >= m_vecAnimFrame.size()) // �ѹ��� �����ϰ�;�
		{
			if (!m_pAnimator->GetRepeat())
				m_pAnimator->SetRepeatcnt();
			m_CurFrame = 0;
			m_fAccTime = 0.f;
		}

	}
}

void Animation::Render(HDC _hdc)
{
	Object* pObj = m_pAnimator->GetOwner();
	Vec2 vPos = pObj->GetPos();

	float scale = GET_SINGLE(ResourceManager)->GetAnimationScale(m_strName);
	int width = (int)(m_vecAnimFrame[m_CurFrame].vSlice.x * scale);
	int height = (int)(m_vecAnimFrame[m_CurFrame].vSlice.y * scale);

	if (!m_IsRotate)
	{
		vPos = vPos + m_vecAnimFrame[m_CurFrame].vOffset;
		TransparentBlt(_hdc
			, (int)(vPos.x - width / 2.f) // X ��ǥ
			, (int)(vPos.y - height / 2.f) // Y ��ǥ
			, width // ��
			, height // ����
			, m_pTex->GetTexDC()
			, (int)(m_vecAnimFrame[m_CurFrame].vLT.x)
			, (int)(m_vecAnimFrame[m_CurFrame].vLT.y)
			, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
			, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y)
			, RGB(255, 0, 255)); // ���� ���� (����)
	}
	else
	{
		if (_rotateDC == NULL)
		{
			_rotateDC = CreateCompatibleDC(_hdc);
			_rotateBitMap = CreateCompatibleBitmap(_hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
			SelectObject(_rotateDC, _rotateBitMap);
		}
		
		float _angle = pObj->GetAngle();
		float halfWidth = width / 2.0f;
		float halfHeight = height / 2.0f;

		float cos = cosf(_angle);
		float sin = sinf(_angle);

		POINT vertices[4];

		// ȸ�� �߽� ��ǥ
		float centerX = vPos.x; // ���� ���� X ��ǥ
		float centerY = vPos.y;           // Y ��ǥ�� �״�� ����

		// �� ������ ȸ�� �� ȭ�� ��ǥ ���
		if (!pObj->isCenter)
		{
			centerX -= halfWidth;
			vertices[0].x = (LONG)(centerX + (0 * cos - (-halfHeight) * sin));
			vertices[0].y = (LONG)(centerY + (0 * sin + (-halfHeight) * cos));

			vertices[1].x = (LONG)(centerX + (width * cos - (-halfHeight) * sin));
			vertices[1].y = (LONG)(centerY + (width * sin + (-halfHeight) * cos));

			vertices[2].x = (LONG)(centerX + (0 * cos - (halfHeight)*sin));
			vertices[2].y = (LONG)(centerY + (0 * sin + (halfHeight)*cos));
		}
		else
		{
			vertices[0].x = (LONG)(centerX + (-halfWidth * cos - halfHeight * sin));
			vertices[0].y = (LONG)(centerY + (-halfWidth * sin + halfHeight * cos));

			vertices[1].x = (LONG)(centerX + (halfWidth * cos - halfHeight * sin));
			vertices[1].y = (LONG)(centerY + (halfWidth * sin + halfHeight * cos));

			vertices[2].x = (LONG)(centerX + (-halfWidth * cos + halfHeight * sin));
			vertices[2].y = (LONG)(centerY + (-halfWidth * sin - halfHeight * cos));
		}

		BitBlt(_rotateDC, 0, 0, width, height, _hdc, 0, 0, SRCCOPY);
		PlgBlt(_rotateDC, vertices, m_pTex->GetTexDC(), (int)(vPos.x - halfWidth), (int)(vPos.y - halfHeight), width, height, NULL, 0, 0);
		vPos = vPos + m_vecAnimFrame[m_CurFrame].vOffset;
		TransparentBlt(_hdc
			, (int)(vPos.x - width / 2.f) // X ��ǥ
			, (int)(vPos.y - height / 2.f) // Y ��ǥ
			, width // ��
			, height // ����
			, m_pTex->GetTexDC()
			, (int)(m_vecAnimFrame[m_CurFrame].vLT.x)
			, (int)(m_vecAnimFrame[m_CurFrame].vLT.y)
			, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
			, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y)
			, RGB(255, 0, 255)); // ���� ���� (����)
	}
}

void Animation::Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, int _framecount, float _fDuration, bool _isRotate, Vec2 _offset)
{
	m_pTex = _pTex;
	m_IsRotate = _isRotate;
	for (int i = 0; i < _framecount; ++i)
	{
		m_vecAnimFrame.push_back(tAnimFrame({ _vLT + _vStep * i, _vSliceSize, _fDuration, _offset }));
	}
}

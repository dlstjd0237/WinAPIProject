#include "pch.h"
#include "CollisionManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Collider.h"
void CollisionManager::Update()
{
	for (UINT Row = 0; Row < (UINT)LAYER::END; ++Row)
	{
		for (UINT Col = Row; Col < (UINT)LAYER::END; ++Col)
		{
			if (m_arrLayer[Row] & (1 << Col))
			{
				//int a = 0;
				CollisionLayerUpdate((LAYER)Row, (LAYER)Col);
			}
		}
	}
}

void CollisionManager::CheckLayer(LAYER _left, LAYER _right)
{
	// �������� ������ ���ô�.
	// ���� ���� LAYER�� ������, ū ���� ��
	UINT Row = (UINT)_left;
	UINT Col = (UINT)_right;
	//Row = min(Row, Col);
	if (Row > Col)
		std::swap(Row, Col);
	//m_arrLayer[Row];
	//Col;

	//// ��Ʈ ����
	// üũ�� �Ǿ��ִٸ�
	if (m_arrLayer[Row] & (1 << Col))
	{
		// üũ Ǯ��
		m_arrLayer[Row] &= ~(1 << Col);
	}
	// üũ�� �ȵǾ��ִٸ�r
	else
	{
		m_arrLayer[Row] |= (1 << Col);
	}
	int a = 0;
}

void CollisionManager::CheckReset()
{
	// �޸� �ʱ�ȭ
	memset(m_arrLayer, 0, sizeof(UINT) * (UINT)LAYER::END);
}

void CollisionManager::CollisionLayerUpdate(LAYER _left, LAYER _right)
{
	std::shared_ptr<Scene> pCurrentScene = GET_SINGLE(SceneManager)->GetCurrentScene();
	const vector<Object*>& vecLeftLayer = pCurrentScene->GetLayerObjects(_left);
	const vector<Object*>& vecRightLayer = pCurrentScene->GetLayerObjects(_right);
	map<ULONGLONG, bool>::iterator iter;
	for (size_t i = 0; i < vecLeftLayer.size(); ++i)
	{
		Collider* pLeftCollider = vecLeftLayer[i]->GetComponent<Collider>();
		// �浹ü ���� ���
		if (nullptr == pLeftCollider)
			continue;
		for (size_t j = 0; j < vecRightLayer.size(); j++)
		{
			Collider* pRightCollider = vecRightLayer[j]->GetComponent<Collider>();
			// �浹ü�� ���ų�, �ڱ��ڽŰ��� �浹�� ���
			if (nullptr == pRightCollider || vecLeftLayer[i] == vecRightLayer[j])
				continue;

			COLLIDER_ID colliderID; // �� �浹ü�θ� ���� �� �ִ� ID
 			colliderID.left_ID = pLeftCollider->GetID();
			colliderID.right_ID = pRightCollider->GetID();

			iter = m_mapCollisionInfo.find(colliderID.ID);
			// ���� ������ �浹�� �� ����.
			if (iter == m_mapCollisionInfo.end())
			{
				// �浹 ������ �̵�ϵ� ������ ��� ���(�浹���� �ʾҴٷ�)
				m_mapCollisionInfo.insert({ colliderID.ID, false });
				//m_mapCollisionInfo[colliderID.ID] = false;
				iter = m_mapCollisionInfo.find(colliderID.ID);
			}

			if (IsCollision(pLeftCollider, pRightCollider))
			{
				// �������� �浹��
				if (iter->second)
				{
					if (vecLeftLayer[i]->GetIsDead() || vecRightLayer[j]->GetIsDead())
					{
						pLeftCollider->ExitCollision(pRightCollider);
						pRightCollider->ExitCollision(pLeftCollider);
						iter->second = false;
					}
					else
					{
						pLeftCollider->StayCollision(pRightCollider);
						pRightCollider->StayCollision(pLeftCollider);
					}
				}
				else // ������ �浹 x
				{
					if (!vecLeftLayer[i]->GetIsDead() && !vecRightLayer[j]->GetIsDead())
					{
						pLeftCollider->EnterCollision(pRightCollider);
						pRightCollider->EnterCollision(pLeftCollider);
						iter->second = true;
					}
				}
			}
			else // �浹 ���ϳ�?
			{
				if (iter->second) // �ٵ� ������ �浹��
				{
					pLeftCollider->ExitCollision(pRightCollider);
					pRightCollider->ExitCollision(pLeftCollider);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::IsCollision(Collider* _left, Collider* _right)
{
	Vec2 vLeftPos = _left->GetLatedUpatedPos();
	Vec2 vRightPos = _right->GetLatedUpatedPos();
	Vec2 vLeftSize = _left->GetSize();
	Vec2 vRightSize = _right->GetSize();

	RECT leftRt = RECT_MAKE(vLeftPos.x, vLeftPos.y, vLeftSize.x, vLeftSize.y);
	RECT rightRt = RECT_MAKE(vRightPos.x, vRightPos.y, vRightSize.x, vRightSize.y);
	RECT rt;
	return ::IntersectRect(&rt, &leftRt, &rightRt);
	/*if (abs(vRightPos.x - vLeftPos.x) < (vLeftSize.x + vRightSize.x) / 2.f
		&& abs(vRightPos.y - vLeftPos.y) < (vLeftSize.y + vRightSize.y) / 2.f)
	{
		return true;
	}

	return false;*/
}

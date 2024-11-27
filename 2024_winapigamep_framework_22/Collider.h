#pragma once
#include "Component.h"
class Collider : public Component
{
public:
    Collider();
    ~Collider();
public:
    // Component��(��) ���� ��ӵ�
    void LateUpdate() override;
    void Render(HDC _hdc) override;
public:
    void EnterCollision(Collider* _other); // �浹����
    void StayCollision(Collider* _other); // �浹��
    void ExitCollision(Collider* _other); // �浹����
    const UINT& GetID() const { return m_ID; }
public:
    void SetSize(Vec2 _vSize) { m_vSize = _vSize; }
    const Vec2& GetSize() const { return m_vSize; }
    void SetOffSetPos(Vec2 _vOffsetPos)
    {
        m_vOffsetPos = _vOffsetPos;
    }
    const Vec2& GetOffSetPos() const { return m_vOffsetPos; }
    const Vec2& GetLatedUpatedPos() const
    {
        return m_vLatePos;
    }
private:
    bool m_showDebug = false;
    UINT m_ID; // �浹ü ���� ID��
    static UINT m_sNextID;

    Vec2 m_vSize; // �ݶ��̴� ũ��
    // Object�κ��� ������� ��ġ
    Vec2 m_vOffsetPos;
    // LateUpdate���� �� �����Ӹ��� ������Ʈ�κ��� ���Ǵ� ��ġ
    Vec2 m_vLatePos;

};


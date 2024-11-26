#pragma once
class Collider;
class RigidBody;
class Component;
class Object
{
public:
	Object();
	virtual ~Object();
public:
	virtual void Update() abstract;
	virtual void LateUpdate();
	virtual void Render(HDC _hdc) abstract;
	void ComponentRender(HDC _hdc);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetSize(Vec2 _vSize) { m_vSize = _vSize; }
	void SetUseGravity(bool _value) { m_IsUseGravity = _value; }
	void SetGravity(float _gravit) { m_gravity = _gravit; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetSize() const { return m_vSize; }
	const float& GetGravity()const { return	 m_gravity; }
public:
	virtual void EnterCollision(Collider* _other);
	virtual void StayCollision(Collider* _other);
	virtual void ExitCollision(Collider* _other);
	const bool& GetIsDead() const { return m_IsDie; }
	void SetDead() { m_IsDie = true; }
	void SetName(wstring _name) { m_name = _name; }
	void UseGravity();
	const wstring& GetName() const { return m_name; }

private:
	bool m_IsDie;
	bool m_IsUseGravity = false;
	float m_gravity = 9.8f;
	wstring m_name;
public:
	template<typename T>
	void AddComponent()
	{
		T* com = new T;
		com->SetOwner(this);
		m_vecComponents.push_back(com);
	}
	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* com : m_vecComponents)
		{
			component = dynamic_cast<T*>(com);
			if (component)
				break;
		}
		return component;
	}
private:
	//POINT m_ptPos;
	//POINT m_ptSize;
	Vec2 m_vPos;
	Vec2 m_vSize;
	float m_vGravity;
	vector<Component*> m_vecComponents;
};


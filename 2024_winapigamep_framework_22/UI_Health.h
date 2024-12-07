#pragma once
#include "Object.h";
#include "Texture.h"
#include <string>

class UI_Health : public Object
{
public:
	UI_Health(wstring bgPath, wstring fillPath, wstring Bgname, wstring amountName, Vec2 Scale);
	//배경경로, 채워질 이미지 경로, 배경이름, 채워질 이미지이름, 스케일
	~UI_Health();

public:
	void Update() override;
	void Render(HDC _hdc) override;
	void SetFillAmount(float _amount);

private:
	float m_fFillAmount;	//Fillamount값
	Texture* m_pBgTex;		//배경 텍스쳐
	Texture* m_pFillTex;	//채워질 이미지 택스쳐
	wstring m_bgpath;
	wstring m_Amountpath;
	wstring m_bgName;
	wstring m_AmountName;
	Vec2 m_scale;
};

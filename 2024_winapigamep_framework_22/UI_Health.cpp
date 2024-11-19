#include "pch.h"
#include "UI_Health.h"

UI_Health::UI_Health()
{
}

void UI_Health::Update()
{
	std::cout << cnt << std::endl;
	cnt--;
}

void UI_Health::Render(HDC _hdc)
{

}

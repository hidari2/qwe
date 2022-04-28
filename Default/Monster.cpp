#include "stdafx.h"
#include "Monster.h"

int CMonster::ST_Point = 1;
CMonster::CMonster()
{
}


CMonster::~CMonster()
{
}

void CMonster::Initialize(void)
{
	m_tInfo.fCX = 40.f;
	m_tInfo.fCY = 40.f;

	m_fSpeed = 2.f;
}

int CMonster::Update(void)
{
	if (m_bDead)
		return DEAD;

	m_tInfo.fX += m_fSpeed * cosf((m_fTheta * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fTheta * PI) / 180.f);

	Update_Rect();

	return NOEVENT;
}

void CMonster::Late_Update(void)
{
	if (DeleteLeft >= m_tInfo.fX || DeleteTop >= m_tInfo.fY || DeleteRight <= m_tInfo.fX || DeleteBottom <= m_tInfo.fY)
	{
		Set_Dead();
	}
}

void CMonster::Render(HDC hDC)
{
	HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hDC, hBlueBrush);
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	SelectObject(hDC, hDefaultBrush);
	DeleteObject(hBlueBrush);
}

void CMonster::Release(void)
{
}

void CMonster::OnCollision(CObj* _pOtherObj)
{ 
	statInfo& GetMonster = _pOtherObj->Get_StatInfo();

	m_tStatInfo.iHp -= GetMonster.iAt;

	m_tInfo.fCX -= 8.f;
	m_tInfo.fCY -= 8.f;

	if (m_tStatInfo.iHp <= 0)
	{
		Set_Dead();
		ST_Point++;
	}

}

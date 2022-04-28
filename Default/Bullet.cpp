#include "stdafx.h"
#include "Bullet.h"


CBullet::CBullet()
{
}


CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize(void)
{
	m_tInfo.fCX = 30.f;
	m_tInfo.fCY = 30.f;

	m_fSpeed = 5.f;

}

int CBullet::Update(void)
{
	if (m_bDead)
		return DEAD;

	m_tInfo.fX += m_fSpeed * cosf((m_fTheta * PI) / 180.f);
	m_tInfo.fY -= m_fSpeed * sinf((m_fTheta * PI) / 180.f);

	Update_Rect();

	return NOEVENT;

}

void CBullet::Late_Update(void)
{
	if (DeleteLeft >= m_tInfo.fX || DeleteTop >= m_tInfo.fY || DeleteRight <= m_tInfo.fX || DeleteBottom <= m_tInfo.fY)
	{
		Set_Dead();
	}
}

void CBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CBullet::Release(void)
{
}

void CBullet::OnCollision(CObj* _pOtherObj)
{
	Set_Dead();
}

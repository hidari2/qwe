#include "stdafx.h"
#include "ChargingBullet.h"

CChargingBullet::CChargingBullet()
	: m_bCharging(true), m_pTarget(nullptr)
{
}


CChargingBullet::~CChargingBullet()
{
	Release();
}

void CChargingBullet::Initialize(void)
{
	m_tInfo.fCX = 20.f;
	m_tInfo.fCY = 20.f;

	m_fSpeed = 5.f;

}

int CChargingBullet::Update(void)
{
	if (m_bDead)
		return DEAD;

	if (!m_bCharging)
	{
		m_tInfo.fX += m_fSpeed * cosf((m_fTheta * PI) / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf((m_fTheta * PI) / 180.f);
	}
	else
	{
		m_tInfo.fX = m_pTarget->Get_Info().fX + (m_pTarget->Get_Info().fCX * 0.5f);
		m_tInfo.fY = m_pTarget->Get_Info().fY;
	}

	Update_Rect();

	return NOEVENT;
}

void CChargingBullet::Late_Update(void)
{
	if (DeleteLeft >= m_tInfo.fX || DeleteTop >= m_tInfo.fY || DeleteRight <= m_tInfo.fX || DeleteBottom <= m_tInfo.fY)
		m_bDead = true;
}

void CChargingBullet::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CChargingBullet::Release(void)
{
}

void CChargingBullet::OnCollision(CObj* _pOtherObj)
{
	Set_Dead();
}

void CChargingBullet::Charge()
{
	m_tInfo.fCX += 0.08f;
	m_tInfo.fCY += 0.08f;
	m_tStatInfo.iAt += 1.f;
}           

void CChargingBullet::Shoot()
{
	m_bCharging = false;
}

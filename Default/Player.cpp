#include "stdafx.h"
#include "Player.h"
#include "MainGame.h"

#include "Player.h"

CPlayer::CPlayer()
	: m_pChargeBullet(nullptr), m_bIsChit(false)
{
}

CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Initialize(void)
{
	m_tInfo.fX = 200.f;
	m_tInfo.fY = 300.f;

	m_tInfo.fCX = 80.f;
	m_tInfo.fCY = 80.f;

	m_fSpeed = 5.f;

	m_fDelay = 1000.f;
	m_fOldTime = GetTickCount();

	m_tStatInfo.iMaxHp = 100;
	m_tStatInfo.iHp = m_tStatInfo.iMaxHp;
	m_tStatInfo.iAt = 10;
}

int CPlayer::Update(void)
{
	if (m_bDead)
		return DEAD;

	Key_Input();

	if (m_fOldTime + m_fDelay < GetTickCount() && !GetAsyncKeyState(VK_SPACE))
	{
		m_pBullet->push_back(CreateBullet());
		m_fOldTime = GetTickCount();
	}

	Update_Rect();

	return	NOEVENT;

}

void CPlayer::Late_Update(void)
{
}

void CPlayer::Render(HDC hDC)
{
	Ellipse(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release(void)
{

}

void CPlayer::Key_Input(void)
{
	if (GetAsyncKeyState('P'))
		m_bIsChit = true;
	if (GetAsyncKeyState('O'))
		m_bIsChit = false;


	if (GetAsyncKeyState(VK_LEFT))
		m_tInfo.fX -= m_fSpeed;

	if (GetAsyncKeyState(VK_RIGHT))
		m_tInfo.fX += m_fSpeed;

	if (GetAsyncKeyState(VK_UP))
		m_tInfo.fY -= m_fSpeed;

	if (GetAsyncKeyState(VK_DOWN))
		m_tInfo.fY += m_fSpeed;

	Key_Space();

}

void CPlayer::Key_Space(void)
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		if (!m_pChargeBullet)
		{
			m_pChargeBullet = new CChargingBullet;
			m_pChargeBullet->Set_Pos(m_tInfo.fX + (m_tInfo.fCX * 0.5f), m_tInfo.fY);
			m_pChargeBullet->SetTarget(this);
			m_pChargeBullet->Set_StatInfo(Get_StatInfo());
			m_pChargeBullet->Initialize();
			m_pChargeBullet->Set_Theta(0.f);

			m_pBullet->push_back(m_pChargeBullet);
		}
		else
		{
			m_pChargeBullet->Charge();
		}
	}
	else
	{
		if (m_pChargeBullet)
		{
			m_pChargeBullet->Shoot();
			m_pChargeBullet = nullptr;
		}
	}
}

CObj* CPlayer::CreateBullet()
{
	CObj* pBullet = new CBullet;
	pBullet->Set_Pos(m_tInfo.fX, m_tInfo.fY);

	pBullet->Set_StatInfo(Get_StatInfo());
	pBullet->Initialize();
	pBullet->Set_Theta(0.f);

	return pBullet;
}

//CObj * CPlayer::CreateChargingBullet()
//{
//	CObj* pChargingBullet = new CChargingBullet;
//	pChargingBullet->Set_Pos(m_tInfo.fX + (m_tInfo.fCX * 0.5f), m_tInfo.fY);
//	pChargingBullet->Initialize();
//	pChargingBullet->Set_Theta(0.f);
//	
//	/*if (m_tInfo.fX == Get_Info().fX - (m_tInfo.fCX * 0.5f))
//		pChargingBullet->Set_Charging(false);*/
//
//	return pChargingBullet;
//}

void CPlayer::OnCollision(CObj* _pOtherObj)
{
	if (m_bIsChit)
		return;


	statInfo& GetMonster = _pOtherObj->Get_StatInfo();

	m_tStatInfo.iHp -= GetMonster.iAt;

	m_tInfo.fCX -= 10.f;
	m_tInfo.fCY -= 10.f;

	if (m_tStatInfo.iHp <= 0)
	{
		Set_Dead();
		CMonster::ST_Point = 0;
		CMainGame::SetScene(START);
	}
}
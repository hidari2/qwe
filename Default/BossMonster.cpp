#include "stdafx.h"
#include "BossMonster.h"
#include "MainGame.h"

CBossMonster::CBossMonster()
{
}


CBossMonster::~CBossMonster()
{
}

void CBossMonster::Initialize(void)
{
	m_tInfo.fCX = 150.f;
	m_tInfo.fCY = 150.f;

	m_fSpeed = 1.f;

	fCooltime1Sec = GetTickCount();
	fCooltime5Sec = GetTickCount();
	fCooltime6Sec = GetTickCount();
	fSpreadCooltime = GetTickCount();

	Bullet_ChangeAngle = 10;

	Bullet_Angle = 150.0f;
}

int CBossMonster::Update(void)
{
	if (m_bDead)
		return DEAD;

	m_tInfo.fY += m_fSpeed;

	Phase_Pattern();

	Update_Rect();

	return NOEVENT;
}

void CBossMonster::Late_Update(void)
{
	if (0 >= m_tRect.top || WINCY <= m_tRect.bottom)
	{
		m_fSpeed = m_fSpeed * -1;
	}
}

void CBossMonster::Render(HDC hDC)
{
	if (m_tStatInfo.iHp > 3)
	{
		HBRUSH hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
		HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hDC, hBlueBrush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, hDefaultBrush);
		DeleteObject(hBlueBrush);
	}
	else
	{
		HBRUSH hBlueBrush = CreateSolidBrush(RGB(255, 0, 0));
		HBRUSH hDefaultBrush = (HBRUSH)SelectObject(hDC, hBlueBrush);
		Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
		SelectObject(hDC, hDefaultBrush);
		DeleteObject(hBlueBrush);
	}

}

void CBossMonster::Release(void)
{
}

void CBossMonster::Phase_Pattern(void)
{
	/*if (m_tStatInfo.iHp >= 5)
	{
		SpreadGun();
	}
	else if (m_tStatInfo.iHp == 4)
	{
		ShotGun();
	}
	else if (m_tStatInfo.iHp == 3)
	{
			StraightGun();
	}*/

	if (fCooltime1Sec + 1000 < GetTickCount() && m_tStatInfo.iHp > 3)
	{
		NormalGun();
		fCooltime1Sec = GetTickCount();
	}
	else if (fCooltime5Sec + 5000 < GetTickCount())
	{
		StraightGun();
		fCooltime5Sec = GetTickCount();
	}
	else if (fCooltime6Sec + 6000 < GetTickCount())
	{
		ShotGun();
		fCooltime6Sec = GetTickCount();
	}
	//phase2
	else if (fCooltime1Sec + 1000 < GetTickCount() && m_tStatInfo.iHp <= 3)
	{
		SquareGun();
		fCooltime1Sec = GetTickCount();
	}
	else if (fSpreadCooltime + 50 < GetTickCount() && m_tStatInfo.iHp <= 3)
	{
		SpreadGun();
		fSpreadCooltime = GetTickCount();
	}

}

CObj* CBossMonster::CreateBossMonsterBullet(float _fTheta, int _fx, int _fy)
{
	CObj* pBullet = new CBullet;
	pBullet->Set_Pos(_fx, _fy);
	pBullet->Initialize();

	pBullet->Set_Theta(_fTheta);

	return pBullet;
}

void CBossMonster::ShotGun()
{
	//if (fOldtime + fDelay < GetTickCount())
	//{
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(150.0f, m_tInfo.fX - 30, m_tInfo.fY));
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX, m_tInfo.fY));
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(210.0f, m_tInfo.fX - 30, m_tInfo.fY));
	//fOldtime = GetTickCount();
	//}
}

void CBossMonster::StraightGun()
{
	//if (fOldtime + fDelay < GetTickCount())
	//{
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX, m_tInfo.fY - 30));
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX, m_tInfo.fY));
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX, m_tInfo.fY + 30));
	//fOldtime = GetTickCount();
//}
}
void CBossMonster::SpreadGun()
{

	//if (fOldtime + fDelay - 800 < GetTickCount())
	//{
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(Bullet_Angle, m_tInfo.fX, m_tInfo.fY));
	m_tInfo.fX - 5;
	m_tInfo.fY + 5;

	Bullet_Angle += Bullet_ChangeAngle;

	if (Bullet_Angle == 270 || Bullet_Angle == 90)
	{
		Bullet_ChangeAngle *= -1;
	}

	//fOldtime = GetTickCount();
//}
}
void CBossMonster::NormalGun()
{
	//if (fOldtime + fDelay < GetTickCount())
	//{
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX, m_tInfo.fY));
	//fOldtime = GetTickCount();
//}
}

void CBossMonster::SquareGun()
{
	//if (fOldtime + fDelay < GetTickCount())
	//{
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX - 30, m_tInfo.fY - 30));
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX + 30, m_tInfo.fY - 30));
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX, m_tInfo.fY));
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX - 30, m_tInfo.fY + 30));
	m_pBossMonsterBullet->push_back(CreateBossMonsterBullet(180.0f, m_tInfo.fX + 30, m_tInfo.fY + 30));
	//fOldtime = GetTickCount();
	//}
}



void CBossMonster::OnCollision(CObj* _pOtherObj)
{
	statInfo& GetBulletStat = _pOtherObj->Get_StatInfo();

	m_tInfo.fCX -= 15.f;
	m_tInfo.fCY -= 15.f;

	if (m_fSpeed > 0)
	{
		m_fSpeed += 0.5f;
	}
	else
	{
		m_fSpeed -= 0.5f;
	}

	m_tStatInfo.iHp -= GetBulletStat.iAt;

	if (m_tStatInfo.iHp <= 0)
	{
		Set_Dead();
		CMainGame::SetScene(CLEAR);
	}

}
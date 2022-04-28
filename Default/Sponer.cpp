#include "stdafx.h"
#include "Sponer.h"
#include "BossMonster.h"
#include "AbstractFactory.h"

CSponer::CSponer()
{
}

CSponer::~CSponer()
{
	Release();
}

void CSponer::Initialize(void)
{
	RIGHT.SPONER_TOP.x = 1340;        //윈도우상 오른쪽 좌표 설정 
	RIGHT.SPONER_BOTTOM.x = 1340;
	RIGHT.SPONER_TOP.y = 30;
	RIGHT.SPONER_BOTTOM.y = 730;

	TOP.SPONER_LEFT.x = 640;
	TOP.SPONER_LEFT.y = -30;
	TOP.SPONER_RIGHT.x = 1280;
	TOP.SPONER_RIGHT.y = -30;

	BOTTOM.SPONER_LEFT.x = 640;
	BOTTOM.SPONER_LEFT.y = 790;
	BOTTOM.SPONER_RIGHT.x = 1280;
	BOTTOM.SPONER_RIGHT.y = 790;

	m_fDelay = 2000.f;
	m_fOldTime = GetTickCount64();
}

int CSponer::Update(void)
{

	if (10 <= CMonster::ST_Point)
	{
		if (m_pBossMonsterList->empty())
		{
			statInfo BossMonsterStat = { 10,10,1 };
			m_pBossMonsterList->push_back(CAbstractFactory<CBossMonster>::Create(1200, 300));
			m_pBossMonsterList->front()->Set_StatInfo(BossMonsterStat);
			((CBossMonster*)(m_pBossMonsterList->front()))->Set_BulletList(m_pBossBulletList);
		}
	}
	else
		GenMonster();

	return NOEVENT;
}

void CSponer::Late_Update(void)
{
}

void CSponer::Render(HDC hDC)
{
	RECT rt = { 10, 20, 100, 100 };
	TCHAR lpOut[1024];
	wsprintf(lpOut, TEXT("Point: %d"), CMonster::ST_Point);
	TextOut(hDC, 10, 20, lpOut, lstrlen(lpOut));
}

void CSponer::Release(void)
{
}


CObj* CSponer::CreateMonster(int iDir)
{
	CObj* pMonster = new CMonster;
	if (iDir == 0)
	{
		LONG SPONERPOINT_BOTTOM;
		SPONERPOINT_BOTTOM = GetRandomNum(BOTTOM.SPONER_LEFT.x, BOTTOM.SPONER_RIGHT.x);
		pMonster->Set_Pos(SPONERPOINT_BOTTOM, BOTTOM.SPONER_LEFT.y);
		statInfo MonsterStat = { 2,2,1 };
		pMonster->Set_StatInfo(MonsterStat);
		pMonster->Set_Theta(GetRandomNum(100.f, 170.f));
		pMonster->Initialize();
	}
	if (iDir == 1)
	{
		LONG SPONERPOINT_TOP;
		SPONERPOINT_TOP = GetRandomNum(TOP.SPONER_LEFT.x, TOP.SPONER_RIGHT.x);
		pMonster->Set_Pos(SPONERPOINT_TOP, TOP.SPONER_LEFT.y);
		statInfo MonsterStat = { 2,2,1 };
		pMonster->Set_StatInfo(MonsterStat);
		pMonster->Set_Theta(GetRandomNum(190.f, 260.f));
		pMonster->Initialize();
	}
	if (iDir == 2)
	{
		LONG SPONERPOINT_RIGHT;
		SPONERPOINT_RIGHT = GetRandomNum(RIGHT.SPONER_TOP.y, RIGHT.SPONER_BOTTOM.y);
		pMonster->Set_Pos(RIGHT.SPONER_TOP.x, SPONERPOINT_RIGHT);
		statInfo MonsterStat = { 2,2,1 };
		pMonster->Set_StatInfo(MonsterStat);
		pMonster->Set_Theta(180.f);
		pMonster->Initialize();
	}

	return pMonster;
}

void CSponer::GenMonster()
{
	if (m_fOldTime + m_fDelay < GetTickCount64())  // 만약에 이전시간값 더하기 쿨타임2초 보다 디버깅한 후 시간보다 작다면 
	{

		iHowMonster = 1;
		for (int i = 0; i < iHowMonster; ++i) {
			m_pMonsterlist->push_back(CreateMonster(0));
			m_pMonsterlist->push_back(CreateMonster(1));
			m_pMonsterlist->push_back(CreateMonster(2));

			// 리스트에 몬스터를 하나 만든다. 
		}
		m_fOldTime = GetTickCount64();  //그리고 이전시간값을 다시 디버깅한 후 시간으로 초기화시킨다. 
	}
}



//pMonster->Set_Pos(1280,rand() % 780+50);
//pMonster->Set_Theta(rand() % 270 + 90);

//LONG SPONERPOINT_RIGHT;
//SPONERPOINT_RIGHT = rand() % RIGHT.SPONER_BOTTOM.y + RIGHT.SPONER_TOP.y;   RIGHT용 
	//pMonster->Set_Pos(RIGHT.SPONER_TOP.x, SPONERPOINT);
	//pMonster->Set_Theta(180.f);

/*LONG SPONERPOINT_TOP;
	SPONERPOINT_TOP = GetRandomNum(TOP.SPONER_LEFT.x ,TOP.SPONER_RIGHT.x);  TOP용
	pMonster->Set_Pos(SPONERPOINT_TOP, TOP.SPONER_LEFT.y);
	pMonster->Set_Theta(GetRandomNum(190.f,260.f));*/
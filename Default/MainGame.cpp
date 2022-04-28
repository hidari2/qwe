#include "stdafx.h"
#include "MainGame.h"
#include "AbstractFactory.h"

#include "BossMonster.h"


SCENE CMainGame::m_eCurScene = START;


CMainGame::CMainGame()
{
}


CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::StartRender(void)
{
	m_hDC = GetDC(g_hWnd);
	RECT rt = { 300, 350, 1000, 500};

	Rectangle(m_hDC, DeleteLeft, DeleteTop, DeleteRight, DeleteBottom);
	DrawText(m_hDC, L"시작하려면 SpaceBar를 누르세요...", -1, &rt, DT_CENTER | DT_WORDBREAK);

	if (GetAsyncKeyState(VK_SPACE))
	{
		m_eCurScene = NONE;
	}

}

void CMainGame::ClearRender(void)
{
	m_hDC = GetDC(g_hWnd);
	RECT rt = { 300, 350, 1000, 500 };

	Rectangle(m_hDC, DeleteLeft, DeleteTop, DeleteRight, DeleteBottom);
	DrawText(m_hDC, L"승리!", -1, &rt, DT_CENTER | DT_WORDBREAK);


}


void CMainGame::Initialize(void)
{
	m_hDC = GetDC(g_hWnd);


	m_pObjList[OBJ_PLAYER].push_back(CAbstractFactory<CPlayer>::Create());
	statInfo PlayerStat = { 5,5,1 };
	((CPlayer*)(m_pObjList[OBJ_PLAYER].front()))->Set_StatInfo(PlayerStat);
	((CPlayer*)(m_pObjList[OBJ_PLAYER].front()))->Set_BulletList(&m_pObjList[OBJ_BULLET]);
	// ((CPlayer*)(m_pObjList[OBJ_PLAYER].front()))->Set_ChargingBulletList(&m_pObjList[OBJ_BULLET]);

	m_pObjList[OBJ_SPONER].push_back(CAbstractFactory<CSponer>::Create());
	((CSponer*)(m_pObjList[OBJ_SPONER].front()))->Set_MonsterList(&m_pObjList[OBJ_MONSTER]);
	((CSponer*)(m_pObjList[OBJ_SPONER].front()))->Set_BossMonsterList(&m_pObjList[OBJ_BOSSMONSTER]);
	((CSponer*)(m_pObjList[OBJ_SPONER].front()))->Set_BossBulletList(&m_pObjList[OBJ_BOSSMONSTERBULLET]);

	//statInfo BossMonsterStat = { 10,10,1 };
	//m_pObjList[OBJ_BOSSMONSTER].push_back(CAbstractFactory<CBossMonster>::Create(1200, 300));
	//((CBossMonster*)(m_pObjList[OBJ_BOSSMONSTER].front()))->Set_StatInfo(BossMonsterStat);
	//((CBossMonster*)(m_pObjList[OBJ_BOSSMONSTER].front()))->Set_BulletList(&m_pObjList[OBJ_BOSSMONSTERBULLET]);

}

void CMainGame::Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end();)
		{
			int iResult = (*iter)->Update();

			if (DEAD == iResult)
			{
				Safe_Delete<CObj*>(*iter);
				iter = m_pObjList[i].erase(iter);
			}
			else
			{
				(*iter)->Update();
				++iter;
			}
		}
	}
}

void CMainGame::Late_Update(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); ++iter)
		{
			(*iter)->Late_Update();
		}
	}

	CCollisionMgr::Collision_Rect(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_MONSTER]);				// 플레이어와 몬스터
	CCollisionMgr::Collision_Rect(m_pObjList[OBJ_PLAYER], m_pObjList[OBJ_BOSSMONSTERBULLET]);	// 플레이어와 보스 총알
	CCollisionMgr::Collision_Rect(m_pObjList[OBJ_MONSTER], m_pObjList[OBJ_BULLET]);				// 몬스터와 플레이어 총알
	CCollisionMgr::Collision_Rect(m_pObjList[OBJ_BOSSMONSTER], m_pObjList[OBJ_BULLET]);			// 보스와 플레이어의 총알
}

void CMainGame::Render(void)
{
	Rectangle(m_hDC, 0, 0, WINCX, WINCY);

	Rectangle(m_hDC, DeleteLeft, DeleteTop, DeleteRight, DeleteBottom);

	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); ++iter)
		{
			(*iter)->Render(m_hDC);
		}
	}
}

void CMainGame::Release(void)
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter = m_pObjList[i].begin(); iter != m_pObjList[i].end(); ++iter)
		{
			Safe_Delete<CObj*>(*iter);
		}
		m_pObjList[i].clear();
	}
	

	ReleaseDC(g_hWnd, m_hDC);	
}

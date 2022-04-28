#pragma once

#include "Include.h"

#include "Obj.h"
#include "Player.h"
#include "Bullet.h"
#include "Monster.h"
#include "CollisionMgr.h"
#include "Sponer.h"

class CMainGame
{
public:	
	CMainGame();
	~CMainGame();

public:
	CObj*		CreateMonster(float _fX, float _fY)
	{
		CObj*	pMonster = new CMonster;
		pMonster->Set_Pos(_fX, _fY);
		pMonster->Initialize();

		return	pMonster;
	}

public:
	static SCENE GetScene() { return m_eCurScene; }
	static void SetScene(SCENE eScene) { m_eCurScene = eScene; }

public:
	void StartRender(void);
	void ClearRender(void);

public:
	void	Initialize(void);		
	void	Update(void);			
	void	Late_Update(void);
	void	Render(void);			
	void	Release(void);			


private:
	HDC		m_hDC;
	list<CObj*>	m_pObjList[OBJ_END];


private:
	static SCENE	m_eCurScene;

};


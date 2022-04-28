#pragma once
#include "Obj.h"
#include "Monster.h"

struct Generator_RIGHT {      //윈도우화면상 오른쪽 관리하는 구조체
	POINT SPONER_TOP;
	POINT SPONER_BOTTOM;
};
struct Generator_TOPBOTTOM {     //윈도우상 위랑 밑 관리하는 구조체 
	POINT SPONER_LEFT;
	POINT SPONER_RIGHT;
};

class CSponer : public CObj
{
public:
	CSponer();
	~CSponer();
public:
	void	Initialize(void);
	int		Update(void);
	void	Late_Update(void);
	void	Render(HDC hDC);
	void	Release(void);
public:
	void		Set_MonsterList(list<CObj*>* _pMonsterlist) { m_pMonsterlist = _pMonsterlist; }//몬스터 클래스의 리스트를 스토너 클래스에서 사용하기 위함임
	void		Set_BossMonsterList(list<CObj*>* _pMonsterlist) { m_pBossMonsterList = _pMonsterlist; }
	void		Set_BossBulletList(list<CObj*>* _pMonsterlist) { m_pBossBulletList = _pMonsterlist; }
	CObj*		CreateMonster(int iDir);      //몬스터를 생성하기 위한 함수
	void		GenMonster();


private:
	list<CObj*>* m_pMonsterlist;     //몬스터리스트를 공유해서 사용하기 위한 포인터 
	list<CObj*>* m_pBossMonsterList;
	list<CObj*>* m_pBossBulletList;

	int iHowMonster;   //몬스터 한틱에 몇개 만들지 올리는 변수 
	 //이전 시간 값
	// 공격 쿨타임 
	Generator_RIGHT RIGHT;  // 윈도우상 오른쪽에서 일직선으로 나오게하는 구조체
	Generator_TOPBOTTOM TOP; //윈도우상 위에서 사르륵 나오게하는 구조체
	Generator_TOPBOTTOM BOTTOM; //윈도우상 아래에서 샬륵 나오게하는 구조체

};



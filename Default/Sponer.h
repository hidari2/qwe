#pragma once
#include "Obj.h"
#include "Monster.h"

struct Generator_RIGHT {      //������ȭ��� ������ �����ϴ� ����ü
	POINT SPONER_TOP;
	POINT SPONER_BOTTOM;
};
struct Generator_TOPBOTTOM {     //������� ���� �� �����ϴ� ����ü 
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
	void		Set_MonsterList(list<CObj*>* _pMonsterlist) { m_pMonsterlist = _pMonsterlist; }//���� Ŭ������ ����Ʈ�� ����� Ŭ�������� ����ϱ� ������
	void		Set_BossMonsterList(list<CObj*>* _pMonsterlist) { m_pBossMonsterList = _pMonsterlist; }
	void		Set_BossBulletList(list<CObj*>* _pMonsterlist) { m_pBossBulletList = _pMonsterlist; }
	CObj*		CreateMonster(int iDir);      //���͸� �����ϱ� ���� �Լ�
	void		GenMonster();


private:
	list<CObj*>* m_pMonsterlist;     //���͸���Ʈ�� �����ؼ� ����ϱ� ���� ������ 
	list<CObj*>* m_pBossMonsterList;
	list<CObj*>* m_pBossBulletList;

	int iHowMonster;   //���� ��ƽ�� � ������ �ø��� ���� 
	 //���� �ð� ��
	// ���� ��Ÿ�� 
	Generator_RIGHT RIGHT;  // ������� �����ʿ��� ���������� �������ϴ� ����ü
	Generator_TOPBOTTOM TOP; //������� ������ �縣�� �������ϴ� ����ü
	Generator_TOPBOTTOM BOTTOM; //������� �Ʒ����� ���� �������ϴ� ����ü

};



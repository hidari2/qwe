#pragma once
#include "Obj.h"

#include "Bullet.h"
#include "Player.h"

class CBossMonster :
	public CObj
{
public:
	CBossMonster();
	virtual ~CBossMonster();
public:
	void		Set_BulletList(list<CObj*>* _pBullet) { m_pBossMonsterBullet = _pBullet; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOtherObj) override;
private:
	void		Phase_Pattern(void);
	CObj* CreateBossMonsterBullet(float _fTheta, int _fx, int _fy);

	void ShotGun();
	void StraightGun();
	void SpreadGun();
	void NormalGun();
	void SquareGun();


private:
	list<CObj*>* m_pBossMonsterBullet;


	float fSpreadCooltime;
	float fCooltime1Sec;
	float fCooltime5Sec;
	float fCooltime6Sec;

	float Bullet_Angle;
	int Bullet_ChangeAngle;
};



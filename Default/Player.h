#pragma once
#include "Obj.h"
#include "Bullet.h"
#include "Monster.h"
#include "ChargingBullet.h"


class CPlayer :
	public CObj
{
public:
	CPlayer();
	virtual ~CPlayer();

public:
	void		Set_BulletList(list<CObj*>* _pBullet) { m_pBullet = _pBullet; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOtherObj) override;

private:
	void		Key_Input(void);
	void		Key_Space(void);
	CObj* CreateBullet();
	// CObj*		CreateChargingBullet();

private:
	list<CObj*>* m_pBullet;
	// list<CObj*>* m_pChargingBullet;
	CChargingBullet* m_pChargeBullet;

	bool	m_bIsChit;

};

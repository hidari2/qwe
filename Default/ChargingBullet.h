#pragma once
#include	"Obj.h"

class CChargingBullet :
	public CObj
{
public:
	CChargingBullet();
	virtual ~CChargingBullet();

public:
	void SetTarget(CObj* pTarget) { m_pTarget = pTarget; }

public:
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual void Late_Update(void) override;
	virtual void Render(HDC hDC) override;
	virtual void Release(void) override;

public:
	virtual void OnCollision(CObj* _pOtherObj) override;


public:
	void	Charge();
	void	Shoot();

private:
	bool		m_bCharging;
	CObj* m_pTarget;
};


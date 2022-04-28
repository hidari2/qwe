#pragma once

#include "Include.h"

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual		void	Initialize(void)	PURE;
	virtual		int		Update(void)		PURE;
	virtual		void	Late_Update(void)	PURE;
	virtual		void	Render(HDC hDC)		PURE;
	virtual		void	Release(void)		PURE;

public:
	void		Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void		Set_Theta(float _fTheta) { m_fTheta = _fTheta; }
	void		Set_Speed(float _fSpeed) { m_fSpeed = _fSpeed; }
	void		Set_Dead() { m_bDead = true; }
	void		Set_StatInfo(statInfo _tInfo) { m_tStatInfo = _tInfo; }

	float		Get_Theta() { return m_fTheta; }
	const RECT&		Get_Rect(void)	const { return m_tRect; }
	const INFO&		Get_Info(void)	const { return m_tInfo; }
    statInfo&	Get_StatInfo(void)  { return m_tStatInfo; }

public:
	virtual		void	OnCollision(CObj* _pOtherObj) {};

protected:
	void		Update_Rect(void);


protected:
	INFO		m_tInfo;
	statInfo    m_tStatInfo;
	RECT		m_tRect;

	float		m_fSpeed;
	float		m_fTheta;
	bool		m_bDead;

	float		m_fDelay;
	float		m_fOldTime;

};


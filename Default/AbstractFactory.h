#pragma once
#include "Obj.h"

template <typename T>
class CAbstractFactory
{
public:
	CAbstractFactory(){}
	~CAbstractFactory(){}

public:
	static	CObj*	Create(void)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		
		return pObj;
	}

	static	CObj*	Create(float _fX, float _fY, float _fTheta = 0.f)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(_fX, _fY);
		pObj->Initialize();
		pObj->Set_Theta(_fTheta);

		return pObj;
	}
};
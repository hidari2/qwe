#include "stdafx.h"
#include "CollisionMgr.h"


CCollisionMgr::CCollisionMgr()
{
}


CCollisionMgr::~CCollisionMgr()
{
}

bool CCollisionMgr::Check_Sphere(CObj * pDest, CObj * pSour)
{
	float fWidth = fabs(pDest->Get_Info().fX - pSour->Get_Info().fX);
	float fHeight = fabs(pDest->Get_Info().fY - pSour->Get_Info().fY);

	float fDiagonal = sqrtf(fWidth*fWidth + fHeight*fHeight);

	float fRadius = (pDest->Get_Info().fCX + pSour->Get_Info().fCX) * 0.5f;
	
	return fRadius > fDiagonal;
}

void CCollisionMgr::Collision_Rect(list<CObj*> _Dest, list<CObj*> _Sour)
{
	RECT rc{};

	for (auto Dest = _Dest.begin(); Dest != _Dest.end(); ++Dest)
	{
		for (auto Sour = _Sour.begin(); Sour != _Sour.end(); ++Sour)
		{
			if (IntersectRect(&rc, &((*Dest)->Get_Rect()), &((*Sour)->Get_Rect())))
			{
				(*Dest)->OnCollision(*Sour);
				(*Sour)->OnCollision(*Dest);
			}
		}
	}
}

void CCollisionMgr::Collision_Sphere(list<CObj*> _Dest, list<CObj*> _Sour)
{
	for (auto Dest = _Dest.begin(); Dest != _Dest.end(); ++Dest)
	{
		for (auto Sour = _Sour.begin(); Sour != _Sour.end(); ++Sour)
		{
			if (Check_Sphere(*Dest,*Sour))
			{
				(*Dest)->OnCollision(*Sour);
				(*Sour)->OnCollision(*Dest);
			}
		}
	}
}

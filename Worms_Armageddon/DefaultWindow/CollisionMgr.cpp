#include "stdafx.h"
#include "CollisionMgr.h"
#include "ObjMgr.h"
#include "Enum.h"
#include "Obj_Map.h"
#include "Obj_Worm.h"
#include "Obj_Projectile.h"

CCollisionMgr*		CCollisionMgr::m_pInstance = nullptr;


CCollisionMgr::CCollisionMgr()
{

}


CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::Update(void)
{

}

void CCollisionMgr::LateUpdate(void)
{
	MapCollision(OBJ_TYPE::WORM,CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::WORM));
	MapCollision(OBJ_TYPE::PROJECTILE, CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::PROJECTILE));
	if (!(CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::PROJECTILE)->empty()))
	{
		Worm_Projectile_Collision();
	}
}

void CCollisionMgr::Initialize(void)
{
	m_pMap = CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::MAP)->front();

	m_hBackDC = static_cast<CObj_Map*>(m_pMap)->Get_BackDC();

	m_vecMapInfo = static_cast<CObj_Map*>(m_pMap)->Get_MapInfo();
}

void CCollisionMgr::Release(void)
{

}

bool CCollisionMgr::MapCollision(OBJ_TYPE _ObjType, list<CObj*>* _pObjList)
{
	switch (_ObjType)
	{
	case OBJ_TYPE::WORM:
		for (auto& iter : *_pObjList)
		{
			WORM_STATE* pWormState = static_cast<CObj_Worm*>(iter)->Get_pState();
			switch (*pWormState)
			{
			case WORM_STATE::FlYING:
				Worm_MapCollision_4Box(iter);
				break;
			case WORM_STATE::NOTTURN:
				break;
			default:
				Worm_MapCollision_Box(iter);
				break;
			}
		}
		break;
	case OBJ_TYPE::PROJECTILE:
		for (auto& iter : *_pObjList)
		{
			if (static_cast<CObj_Projectile*>(iter)->Get_ProjectileState() == PROJECTILE_STATE::NONE && iter->Is_CanCollision())
			{
				switch (static_cast<CObj_Projectile*>(iter)->Get_WeaponType())
				{
				case WEAPON_TYPE::SHEEP:
					Sheep_MapCollision(iter);
					break;
				default:
					Obj_MapCollision(iter);
					break;
				}
			}
		}
		break;
	}

	return false;
}

bool CCollisionMgr::Worm_MapCollision_Box(CObj* _pObj)
{
	CMyVector2 vBottom = static_cast<CObj_Worm*>(_pObj)->Get_Bottom();

	float fX = (UINT)(vBottom.fX - vBottom.fCX * 0.5f);
	float fY = (UINT)(vBottom.fY - vBottom.fCY * 0.5f);

	if (fX < 0.0f || fX + vBottom.fCX * 0.5 > 3950.0f)
	{
		return false;
	}

	if (fY < 0.0f || fY + vBottom.fCY * 0.5f > 1250.0f)
	{
		return false;
	}

	vector<bool>& BoundingBox = _pObj->Get_BoundingBox();

	bool  bCollision = false;

	CMyVector2	vClosest = { 0.0f,0.0f };
	float		fClosestLength = 0.0f;

	if (fY > 820.0f)
		int iTemp = 0;

	for (int x = 0; vBottom.fCX > x; ++x)
	{
		for (int y = 0; vBottom.fCY > y; ++y)
		{
			
			if ((*m_vecMapInfo)[(UINT)((fX + x) + ((fY + y) * 4000))] == true)
			{
				BoundingBox[x + (y * vBottom.fCX)] = true;
				bCollision = true;
				float fLength = sqrt(pow((vBottom.fX - (fX + x)), 2) + pow((vBottom.fY - (fY + y)), 2));
				if (fClosestLength == 0.0f || fClosestLength > fLength)
				{
					vClosest.fX = fX + x;
					vClosest.fY = fY + y;
					fClosestLength = fLength;
				}
			}
		}
	}
	if (!bCollision)
		return false;
	else
	{
		_pObj->Set_MapCollision(vClosest.fX, vClosest.fY);
	}

	return false;
}

bool CCollisionMgr::Worm_MapCollision_Line(CObj * _pObj)
{
	float fLength = _pObj->Get_fLineLength();
	int iX = int(_pObj->Get_Pos().fX - (fLength * 0.5f));
	int iY = int(_pObj->Get_Pos().fY - (fLength * 0.5f));

	if (iX < 0.0f || iX + fLength * 0.5f > 4000.0f)
	{
		return false;
	}

	if (iY < 0.0f || iY + fLength * 0.5f > 1300.0f)
	{
		return false;
	}
	

	vector<bool>& vecLineX = _pObj->Get_LinePixelX();
	vector<bool>& vecLineY = _pObj->Get_LinePixelY();


	bool  bCollision = false;


	for (int x = 0; (int)fLength > x; ++x)
	{
		if ((*m_vecMapInfo)[(UINT)((iX + x) + (iY * 4000))] == true)
		{
			vecLineX[x] = true;
			bCollision = true;
		}
	}

	for (int y = 0; (int)fLength > y; ++y)
	{
		if ((*m_vecMapInfo)[(UINT)((iX) + ((iY + y) * 4000))] == true)
		{
			vecLineY[y] = true;
			bCollision = true;
		}
			
	}

	if (!bCollision)
		return false;
	else
	{
		_pObj->Set_MapCollision(0.0f, 0.0f);
	}


	return false;
}

bool CCollisionMgr::Worm_MapCollision_4Box(CObj * _pObj)
{
	int iDistance = _pObj->Get_BoxDistance();
	vector<bool>* pLeft = _pObj->Get_LeftBox();
	vector<bool>* pTop = _pObj->Get_TopBox();
	vector<bool>* pRight = _pObj->Get_RightBox();
	vector<bool>* pBottom = _pObj->Get_BottomBox();

	int iLeftX = _pObj->Get_Pos().fX - iDistance - 3;
	int iLeftY = _pObj->Get_Pos().fY - 8.0f;

	int iTopX = _pObj->Get_Pos().fX - iDistance;
	int iTopY = _pObj->Get_Pos().fY - iDistance - 3;

	int iRightX = _pObj->Get_Pos().fX + iDistance + 3;
	int iRightY = _pObj->Get_Pos().fY - 8.0f;

	int iBottomX = _pObj->Get_Pos().fX - iDistance;
	int iBottomY = _pObj->Get_Pos().fY + iDistance + 3;


	bool  bCollision = false;
	bool  bLeftCollision = false;
	bool  bRightCollision = false;
	bool  bTopCollision = false;
	bool  bBottomCollision = false;



	for (int x = 0; 5 > x; ++x)
	{
		for (int y = 0; 15 > y; ++y)
		{
			if ((*m_vecMapInfo)[(UINT)((iLeftX + x) + ((iLeftY + y) * 4000))] == true)
			{
				(*pLeft)[x + (5 * y)] = true;
				bCollision = true;
				bLeftCollision = true;
				break;
			}
		}
		if (bLeftCollision)
			break;
	}

	for (int x = 0; 30 > x; ++x)
	{
		for (int y = 0; 5 > y; ++y)
		{
			if ((*m_vecMapInfo)[(UINT)((iTopX + x) + ((iTopY + y) * 4000))] == true)
			{
				(*pTop)[x + (30 * y)] = true;
				bCollision = true;
				bTopCollision = true;
				break;
			}
		}
		if (bTopCollision)
			break;
	}

	for (int x = 0; 5 > x; ++x)
	{
		for (int y = 0; 15 > y; ++y)
		{
			if ((*m_vecMapInfo)[(UINT)((iRightX + x) + ((iRightY + y) * 4000))] == true)
			{
				(*pRight)[x + (5 * y)] = true;
				bCollision = true;
				bRightCollision = true;
				break;
			}
		}
		if (bRightCollision)
			break;
	}

	for (int x = 0; 30 > x; ++x)
	{
		for (int y = 0; 5 > y; ++y)
		{
			if ((*m_vecMapInfo)[(UINT)((iBottomX + x) + ((iBottomY + y) * 4000))] == true)
			{
				(*pBottom)[x + (30 * y)] = true;
				bCollision = true;
				bBottomCollision = true;
				break;
			}
		}
		if (bBottomCollision)
			break;
	}


	if (!bCollision)
		return false;
	else
	{
		_pObj->Set_MapCollision(0.0f, 0.0f);
	}

	return false;
}

bool CCollisionMgr::Obj_MapCollision(CObj * _pObj)
{
	CMyVector2 vCollision = _pObj->Get_Collision();

	int iX = (_pObj->Get_Pos().fX - vCollision.fCX * 0.5f);
	int iY = (_pObj->Get_Pos().fY - vCollision.fCY * 0.5f);

	if (iX < 0.0f || iX + vCollision.fCX * 0.5f > 4000.0f)
	{
		return false;
	}

	if (iY < 0.0f || iY + vCollision.fCY * 0.5f > 1300.0f)
	{
		return false;
	}

	bool  bCollision = false;

	CMyVector2	vClosest = { 0.0f,0.0f };

	for (int x = 0; vCollision.fCX > x; ++x)
	{
		for (int y = 0; vCollision.fCY > y; ++y)
		{
			if ((*m_vecMapInfo)[(UINT)((iX + x) + ((iY + y) * 4000))] == true)
			{
				_pObj->Get_BoundingBox()[x + (y * vCollision.fCX)] = true;
				bCollision = true;
			}
		}
	}
	if (!bCollision)
		return false;
	else
	{
		_pObj->Set_MapCollision(vClosest.fX, vClosest.fY);
		return true;
	}

	return false;
}

bool CCollisionMgr::Sheep_MapCollision(CObj * _pObj)
{
	CMyVector2 vCollision = _pObj->Get_Collision();

	bool  bCollision = false;

	int iX = (_pObj->Get_Pos().fX - vCollision.fCX * 0.5f);
	int iY = (_pObj->Get_Pos().fY - vCollision.fCY * 0.5f);

	int iLength = int(_pObj->Get_fLineLength());

	if (iX < 0.0f || iX + vCollision.fCX * 0.5f > 4000.0f)
	{
		return false;
	}

	if (iY < 0.0f || iY + vCollision.fCY * 0.5f > 1300.0f)
	{
		return false;
	}

	CMyVector2	vClosest = { 0.0f,0.0f };

	for (int x = 0; vCollision.fCX > x; ++x)
	{
		for (int y = 0; vCollision.fCY > y; ++y)
		{
			if ((*m_vecMapInfo)[(UINT)((iX + x) + ((iY + y) * 4000))] == true)
			{
				_pObj->Get_BoundingBox()[x + (y * vCollision.fCX)] = true;
				bCollision = true;
			}
		}
	}


	iX = _pObj->Get_Pos().fX - (iLength * 0.5f);
	iY = _pObj->Get_Pos().fY;

	for (int x = 0; iLength > x; ++x)
	{
		if ((*m_vecMapInfo)[(UINT)((iX + x) + (iY * 4000))] == true)
		{
			_pObj->Get_LinePixelX()[x] = true;
			bCollision = true;
			break;
		}
	}




	if (!bCollision)
		return false;
	else
	{
		_pObj->Set_MapCollision(vClosest.fX, vClosest.fY);
		return true;
	}



	return false;
}

bool CCollisionMgr::Worm_Projectile_Collision(void)
{
	list<CObj*>* pWormList = CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::WORM);
	list<CObj*>* pProjectileList = CObjMgr::Get_Inst()->Get_ObjList(OBJ_TYPE::PROJECTILE);

	for (auto& PJiter : *pProjectileList)
	{
		if (static_cast<CObj_Projectile*>(PJiter)->Get_ProjectileState() == PROJECTILE_STATE::BOMB)
		{
			for (auto& Wormiter : *pWormList)
			{
				W_P_Collision(Wormiter, PJiter);
			}
		}
	}


	return false;
}

bool CCollisionMgr::W_P_Collision(CObj * _pWorm, CObj * _pProjectile)
{
	CMyVector2 vExplosion = static_cast<CObj_Projectile*>(_pProjectile)->Get_Explosion();

	float fWidth = _pWorm->Get_Pos().fX - vExplosion.fX;
	float fHeight = _pWorm->Get_Pos().fY - vExplosion.fY;
	float fLength = sqrt(fWidth * fWidth + fHeight * fHeight);

	if (vExplosion.fCX * 0.5f + 40.0f > fLength)
	{
		_pWorm->Set_BombCollision(vExplosion, static_cast<CObj_Projectile*>(_pProjectile)->Get_Damage(),_pProjectile);
		return true;
	}

	return false;
}



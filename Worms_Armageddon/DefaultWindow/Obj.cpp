#include "stdafx.h"
#include "Obj.h"
#include "Enum.h"

CObj::CObj()
	:m_vPos(CMyVector2(0.0f, 0.0f)), m_pMover(nullptr), m_ObjDir(OBJ_DIR::LEFT), m_bMapCollision(false), m_vClosest(CMyVector2(0.0f,0.0f)), m_bBombCollision(false), m_bDead(false),
	m_iGetDamage(0), m_bAction(false), m_bCanCollision(true), m_pCollObj(nullptr)
{

}


CObj::~CObj()
{
}

void CObj::Update_Rect(void)
{
	m_tRect.left = (LONG)(m_vPos.fX - m_vPos.fCX * 0.5f);
	m_tRect.right = (LONG)(m_vPos.fX + m_vPos.fCX * 0.5f);
	m_tRect.bottom = (LONG)(m_vPos.fY + m_vPos.fCY * 0.5f);
	m_tRect.top = (LONG)(m_vPos.fY - m_vPos.fCY * 0.5f);

}

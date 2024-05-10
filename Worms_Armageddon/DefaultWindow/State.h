#pragma once
#include "Obj.h"
#include "Sprite.h"


class CState
{
public:
	CState();
	virtual ~CState();

	virtual void			Initialize(CObj* _pOwner) PURE;
	virtual void			Update(void) PURE;
	virtual void			LateUpdate(void) PURE;
	virtual void			Release(void) PURE;


protected:
	CObj*					m_pOwner;
	CSprite*				m_pSprite;
	CMyVector2*				m_pPos;
	OBJ_DIR*				m_pObjDir;
};


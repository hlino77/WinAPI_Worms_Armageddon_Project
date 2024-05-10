#pragma once
#include "Obj.h"

class CMyImage  
{
public:
	CMyImage();
	virtual ~CMyImage();

	virtual	void				Initialize(CObj* _pObj) PURE;
	virtual void				Update(void) PURE;
	virtual void				LateUpdate(void) PURE;
	virtual void				Render(HDC _hDC) PURE;
	virtual void				Set_Size(void) PURE;

	virtual void				Reset(void) PURE;


protected:
	CObj*						m_pOwner;
	OBJ_DIR						m_CurrDir;


	int							m_iMax;
	int							m_iCurr;

	float						m_fTargetAngle;
	float*						m_pOwnerAngle;
	float						m_fAngle;

	float						m_fLength;

	HDC							m_hCurrDC;

	float						m_fCX;
	float						m_fCY;

	int							m_iR;
	int							m_iG;
	int							m_iB;
};


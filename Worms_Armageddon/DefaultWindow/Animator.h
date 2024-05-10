#pragma once
#include "Define.h"
#include "Obj.h"
#include "Sprite.h"
#include "MyImage.h"
#include <map>

class CAnimator
{
public:
	CAnimator();
	virtual ~CAnimator();


	virtual	void		Initialize(CObj* _pObj) PURE;
	virtual void		Update(void) PURE;
	virtual void		LateUpdate(void) PURE;
	virtual void		Render(HDC _hDC) PURE;
	virtual void		Release(void) PURE;

	virtual void		Add_Sprite(void) PURE;
	virtual void		Add_Bmp(void) PURE;

	CSprite*			Get_CurrSprite(void) { return m_pCurrSprite; }
protected:
	CObj*							m_pOwner;
	map<const TCHAR*, CSprite*>		m_SpriteList;
	map<const TCHAR*, CMyImage*>	m_BmpList;

	ANIMATOR_STATE					m_CurrAniState;
	CSprite*						m_pCurrSprite;

	CMyImage*						m_pCurrBmp;
};


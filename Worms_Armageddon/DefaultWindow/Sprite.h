#pragma once
#include "Define.h"
#include "Obj.h"
#include "BmpMgr.h"

class CSprite
{
public:
	CSprite();
	virtual ~CSprite();

	virtual	void				Initialize(CObj* _pObj) PURE;
	virtual void				Update(void) PURE;
	virtual void				LateUpdate(void) PURE;
	virtual void				Render(HDC _hDC) PURE;
	virtual void				Set_Size(void) PURE;

	virtual void				SpriteReset(void) { m_iCurr = 0; m_SpriteState = SPRITE_STATE::END; }

	virtual void				Set_Curr(int _iCurr) { m_iCurr = _iCurr; }
							
	SPRITE_STATE				Get_SpriteState(void) { return m_SpriteState; }
protected:
	CObj*			m_pOwner;
	OBJ_DIR			m_CurrDir;


	//스프라이트 속도
	DWORD			m_SpriteTime;
	DWORD			m_DelayTime;

	//스프라이트 딜레이
	DWORD			m_SpriteDelay;
	DWORD			m_PrevSpriteTime;

	SPRITE_STATE	m_SpriteState;

	//스프라이트 현재 수와 최대수
	int				m_iMax;
	int				m_iCurr;


	HDC			m_hCurrDC;

	float			m_fCX;
	float			m_fCY;

	//스프라이트 위치
	float			m_fX;
	float			m_fY;


	
};


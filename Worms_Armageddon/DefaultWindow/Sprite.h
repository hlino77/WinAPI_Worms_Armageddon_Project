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


	//��������Ʈ �ӵ�
	DWORD			m_SpriteTime;
	DWORD			m_DelayTime;

	//��������Ʈ ������
	DWORD			m_SpriteDelay;
	DWORD			m_PrevSpriteTime;

	SPRITE_STATE	m_SpriteState;

	//��������Ʈ ���� ���� �ִ��
	int				m_iMax;
	int				m_iCurr;


	HDC			m_hCurrDC;

	float			m_fCX;
	float			m_fCY;

	//��������Ʈ ��ġ
	float			m_fX;
	float			m_fY;


	
};


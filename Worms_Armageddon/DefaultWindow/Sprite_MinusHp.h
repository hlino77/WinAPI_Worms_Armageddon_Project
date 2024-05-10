#pragma once
#include "Sprite.h"
#include "MyImage.h"

class CSprite_MinusHp : public CSprite
{
public:
	CSprite_MinusHp();
	virtual ~CSprite_MinusHp();

	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Set_Size(void) override;
	void					Release(void);

	void					Reset_MinusHp(CMyVector2 _pPos, int _iNum, int _iTeamNum);
private:
	DWORD					m_iStartTime;
	DWORD					m_iDelay;

	void						Render_Hp(HDC _hDC);
	CMyImage*					m_pHpBox;
	CMyImage*					m_pFont;

	float						m_fSpeedY;
	int							m_iHp;
	int							m_iTeamNum;
	CMyVector2					m_vPos;
};


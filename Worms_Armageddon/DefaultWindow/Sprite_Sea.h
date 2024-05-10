#pragma once
#include "Sprite.h"
class CSprite_Sea : public CSprite
{
public:
	CSprite_Sea();
	virtual ~CSprite_Sea();

	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Set_Size(void) override;

	void					Set_Pos(CMyVector2 _vPos) { m_fX = _vPos.fX; m_fY = _vPos.fY; };
private:
};


#pragma once
#include "Sprite.h"
class CSprite_Cloud : public CSprite
{
public:
	CSprite_Cloud();
	virtual ~CSprite_Cloud();

	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Set_Size(void) override;
private:
	CLOUD_TYPE				m_CurrType;

	void					Set_Cloud(void);

};


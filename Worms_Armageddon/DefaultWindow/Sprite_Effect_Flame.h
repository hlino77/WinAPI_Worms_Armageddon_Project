#pragma once
#include "Sprite.h"
class CSprite_Effect_Flame : public CSprite
{
public:
	CSprite_Effect_Flame();
	virtual ~CSprite_Effect_Flame();


	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Set_Size(void) override;

	void					Flame_Reset(void);
private:
};


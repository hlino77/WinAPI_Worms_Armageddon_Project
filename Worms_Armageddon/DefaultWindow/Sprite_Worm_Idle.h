#pragma once
#include "Sprite.h"
class CSprite_Worm_Idle : public CSprite
{
public:
	CSprite_Worm_Idle();
	virtual ~CSprite_Worm_Idle();


	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;


	virtual void			Set_Size(void) override {};
private:

	void					Idle_Render(HDC _hDC);
	void					Change_Dir(void);

	void					Set_Angle(void);

	
};


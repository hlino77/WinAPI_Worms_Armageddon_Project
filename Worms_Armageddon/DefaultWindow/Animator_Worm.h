#pragma once
#include "Obj.h"
#include "Animator.h"

class CAnimator_Worm : public CAnimator
{
public:
	CAnimator_Worm();
	virtual ~CAnimator_Worm() override;

	virtual void			Initialize(CObj* _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Release(void) override;

	virtual void			Add_Sprite(void) override;
	virtual void			Add_Bmp(void) override;
	void					Reset_WeaponIdle(void);
private:
	


	WORM_STATE		m_CurrState;

	void			Set_Idle(void);
	void			Set_Walk(void);
	void			Set_DrawWeapon(void);
	void			Set_WeaponIdle(void);
	void			Set_Jump(void);
	void			Set_Flying(void);
	void			Set_Slide(void);
	void			Set_Dead(void);
	void			Set_Winner(void);
	void			Set_Swim(void);
};


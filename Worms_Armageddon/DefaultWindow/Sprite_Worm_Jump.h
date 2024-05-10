#pragma once
#include "Sprite.h"
class CSprite_Worm_Jump : public CSprite
{
public:
	CSprite_Worm_Jump();
	virtual ~CSprite_Worm_Jump();


	virtual void			Initialize(CObj * _pObj) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Render(HDC _hDC) override;
	virtual void			Set_Size(void) override;


private:
	void					Change_State(void);

	void					Insert_Bmp(void);
	WORM_JUMP_STATE			m_WormJumpState;

	bool					m_bChangeState;

	void					Set_Jump(void);
	void					Set_JumpReady(void);
	void					Set_FlyUp(void);
	void					Set_Fly(void);
	void					Set_FlyDown(void);
	void					Set_Land(void);


	float					m_fLeftAngle;
	float					m_fRightAngle;
	void					Set_Angle(void);
};


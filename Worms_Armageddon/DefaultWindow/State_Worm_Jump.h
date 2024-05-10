#pragma once
#include "State_Worm.h"
class CState_Worm_Jump : public CState_Worm
{
public:
	CState_Worm_Jump();
	virtual ~CState_Worm_Jump();

	virtual void			Initialize(CObj * _pOwner) override;
	virtual void			Update(void) override;
	virtual void			LateUpdate(void) override;
	virtual void			Release(void) override;
	virtual void			Key_Input(void) override;

private:
	
	void					Worm_Map_Collision(void);
	void					DownCollision(void);
	void					RoundCollision(void);

	float					m_fCenterX;
	float					m_fCenterY;
	float					m_fRightX;
	float					m_fRightY;
	float					m_fLeftX;
	float					m_fLeftY;

	float					m_fBottomLength;

	DWORD					m_JumpDelay;
	DWORD					m_JumpStartTime;

	void					Set_BottomAngle(void);
};

